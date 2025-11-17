#include "FreeRTOS.h"
#include "task.h"
#include <libopencm3/stm32/gpio.h>

void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;

    for (;;) {
        gpio_toggle(GPIOC, GPIO13);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
