// usb_task.c
#include "usb_task.h"
#include "usbserial.h"
#include "FreeRTOS.h"
#include "task.h"
#include <libopencm3/stm32/gpio.h>

//extern char command;   // declared in usbserial.h
extern char usbserial_command;

static void usbTask(void *args)
{
    usbserial_init();
    gpio_clear(GPIOC, GPIO13);

    for(;;)
    {
        usbserial_pool();

        if (usbserial_command != '\0')
        {
            switch (usbserial_command)
            {
                case '0':
                    usbserial_writeline("turning led off");
                    gpio_set(GPIOC, GPIO13);
                    break;

                case '1':
                    usbserial_writeline("turning led on");
                    gpio_clear(GPIOC, GPIO13);
                    break;

                case 't':
                    usbserial_writeline("toggling led state");
                    gpio_toggle(GPIOC, GPIO13);
                    break;

                case 'g':
                {
                    int pa = gpio_get(GPIOA, 0xFF);
                    int pb = gpio_get(GPIOB, 0xFF);
                    int pc = gpio_get(GPIOC, GPIO13);

                    usbserial_writeline("GPIO PORT STATUSES");
                    usbserial_write("A: "); usbserial_write_int(pa, 2); usbserial_writeline("");
                    usbserial_write("B: "); usbserial_write_int(pb, 2); usbserial_writeline("");
                    usbserial_write("C: "); usbserial_write_int(pc, 2); usbserial_writeline("");
                }
                break;

                default:
                    usbserial_writeline("unknown command");
                    break;
            }

            usbserial_command = '\0';
        }
    }
}

void startUsbTask(void)
{
    xTaskCreate(usbTask, "usb", 200, NULL, configMAX_PRIORITIES - 1, NULL);
}
