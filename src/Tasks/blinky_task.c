// usb_task.c
#include "FreeRTOS.h"
#include "task.h"
#include <libopencm3/stm32/gpio.h>
#include "blinky_task.h"
static void blinkyTask(void *args)
{
    for (;;)
    {
        gpio_toggle(GPIOC, GPIO13);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
void startBlinkyTask(void)
{
    xTaskCreate(blinkyTask, "blink", 200, NULL, configMAX_PRIORITIES - 1, NULL);
}
