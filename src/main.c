#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "usb_task.h"
//#include "usbserial.h"
#include "FreeRTOS.h"
#include "task.h"
#include "blinky_task.h"
#include "Led.hpp"
Led red(12);
void SetupButton(void)
{
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(
        GPIOC,
        GPIO_MODE_INPUT,
        GPIO_CNF_INPUT_PULL_UPDOWN,
        GPIO14
    );
    gpio_set(GPIOC, GPIO14);
}
int main(void)
{
    //rcc_clock_setup_in_hse_8mhz_out_72mhz();
    blinkySetup();
    SetupButton();    
    startUsbTask();
    startBlinkyTask();
    vTaskStartScheduler();

    for (;;);
    return 0;
}
