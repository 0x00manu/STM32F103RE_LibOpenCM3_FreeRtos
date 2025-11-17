#ifndef USBSERIAL_H
#define USBSERIAL_H

#include <stdint.h>
#include <libopencm3/usb/usbd.h>

/* API Functions */
void usbserial_init(void);
void usbserial_pool(void);

void usbserial_write(const char *str);
void usbserial_writeline(const char *str);
void usbserial_write_int(int value, int base);

/* Exposed command buffer */
extern char usbserial_command;

#endif
