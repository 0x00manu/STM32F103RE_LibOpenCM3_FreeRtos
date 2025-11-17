#include "usbserial.h"

#include <string.h>
#include <stdlib.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

/* ================================================================
   Global USB State
   ================================================================ */
usbd_device *usbd_dev;

char usbserial_command = '\0';  // <--- replaces "command" in your code

static char usb_serial_str[13];
static char tx_buffer[256];
static int tx_remaining = 0;

/* =================================================================
   USB Descriptors (unchanged from your version)
   ================================================================= */

static const struct usb_device_descriptor dev = {
    .bLength = USB_DT_DEVICE_SIZE,
    .bDescriptorType = USB_DT_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = USB_CLASS_CDC,
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 64,
    .idVendor = 0x0483,
    .idProduct = 0x5740,
    .bcdDevice = 0x0200,
    .iManufacturer = 1,
    .iProduct = 2,
    .iSerialNumber = 3,
    .bNumConfigurations = 1,
};

static uint8_t usbd_control_buffer[128];

/* ---------------- USB CDC Callbacks ---------------- */

static enum usbd_request_return_codes
cdcacm_control_request(usbd_device *usbd_dev,
                       struct usb_setup_data *req,
                       uint8_t **buf,
                       uint16_t *len,
                       void (**complete)(usbd_device *, struct usb_setup_data *))
{
    (void)buf;
    (void)len;
    (void)complete;

    if (req->bRequest == USB_CDC_REQ_SET_CONTROL_LINE_STATE) {
        return USBD_REQ_HANDLED;
    }

    if (req->bRequest == USB_CDC_REQ_SET_LINE_CODING) {
        return USBD_REQ_HANDLED;
    }

    return USBD_REQ_NOTSUPP;
}

/* Receive callback */
static void cdcacm_data_rx_cb(usbd_device *dev, uint8_t ep)
{
    (void)dev;
    (void)ep;

    char buf[64];
    int len = usbd_ep_read_packet(usbd_dev, 0x01, buf, 64);

    if (len > 0) {
        usbserial_command = buf[0];   // <--- single character command
    }
}

static void cdcacm_set_config(usbd_device *dev, uint16_t wValue)
{
    (void)wValue;
    usbd_ep_setup(dev, 0x01, USB_ENDPOINT_ATTR_BULK, 64, cdcacm_data_rx_cb);
    usbd_ep_setup(dev, 0x82, USB_ENDPOINT_ATTR_BULK, 64, NULL);
    usbd_ep_setup(dev, 0x83, USB_ENDPOINT_ATTR_INTERRUPT, 16, NULL);

    usbd_register_control_callback(dev,
                                   USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
                                   USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
                                   cdcacm_control_request);
}

/* --------------------------------------------------------------
   Serial Number Generator
   -------------------------------------------------------------- */
static void fill_usb_serial(void)
{
    uint8_t *id = (uint8_t *)DESIG_UNIQUE_ID_BASE;

    uint8_t raw[6] = {
        id[11],
        id[10] + id[2],
        id[9],
        id[8] + id[0],
        id[7],
        id[6]
    };

    static const char hex[] = "0123456789ABCDEF";
    char *out = usb_serial_str;

    for (int i = 0; i < 6; i++) {
        *out++ = hex[(raw[i] >> 4) & 0xF];
        *out++ = hex[raw[i] & 0xF];
    }
    *out = '\0';
}

/* ================================================================
   PUBLIC API FUNCTIONS
   ================================================================ */

void usbserial_init(void)
{
    rcc_periph_clock_enable(RCC_AFIO);
    AFIO_MAPR |= AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_ON;

    fill_usb_serial();

    static const char *usb_strings[] = {
        "YNSRC Open Source",
        "Blue Pill",
        usb_serial_str
    };

    //extern const struct usb_config_descriptor config;
    const struct usb_config_descriptor config;

    usbd_dev = usbd_init(&st_usbfs_v1_usb_driver,
                         &dev,
                         &config,
                         usb_strings,
                         3,
                         usbd_control_buffer,
                         sizeof(usbd_control_buffer));

    usbd_register_set_config_callback(usbd_dev, cdcacm_set_config);
}

void usbserial_pool(void)
{
    usbd_poll(usbd_dev);

    while (tx_remaining > 0) {
        int sent = usbd_ep_write_packet(usbd_dev, 0x82, tx_buffer, tx_remaining);
        tx_remaining -= sent;
    }
}

void usbserial_write(const char *str)
{
    int len = strlen(str);
    memcpy(tx_buffer + tx_remaining, str, len);
    tx_remaining += len;
}

void usbserial_writeline(const char *str)
{
    usbserial_write(str);
    usbserial_write("\r\n");
}

void usbserial_write_int(int value, int base)
{
    char buff[16];
    itoa(value, buff, base);
    usbserial_write(buff);
}
