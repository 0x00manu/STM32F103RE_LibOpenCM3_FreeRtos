#include "usbserial.h"
#include <libopencm3/stm32/gpio.h>

void handleUsbCommand(char cmd)
{
    switch (cmd)
    {
        case '0':
            usbserial_writeline("LED OFF");
            gpio_set(GPIOC, GPIO13);
            break;

        case '1':
            usbserial_writeline("LED ON");
            gpio_clear(GPIOC, GPIO13);
            break;

        case 't':
            usbserial_writeline("TOGGLE LED");
            gpio_toggle(GPIOC, GPIO13);
            break;

        case 'g':
        {
            int pa = gpio_get(GPIOA, 0xFF);
            int pb = gpio_get(GPIOB, 0xFF);
            int pc = gpio_get(GPIOC, GPIO13);

            usbserial_writeline("GPIO STATUS");
            usbserial_write("A: "); usbserial_write_int(pa, 2); usbserial_writeline("");
            usbserial_write("B: "); usbserial_write_int(pb, 2); usbserial_writeline("");
            usbserial_write("C: "); usbserial_write_int(pc, 2); usbserial_writeline("");
        }
        break;

        default:
            usbserial_writeline("Unknown command");
            break;
    }
}
