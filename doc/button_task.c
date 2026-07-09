#include "FreeRTOS.h"
#include "task.h"
#include <libopencm3/stm32/gpio.h>
//#include <libopencm3/stm32/rcc.h>
//#include <libopencm3/cm3/nvic.h>
//#include <libopencm3/stm32/exti.h>
#include "button_task.h"
static TaskHandle_t buttonTaskHandle = NULL;
TaskHandle_t ButtonTask_GetHandle(void);
void ButtonTask(void *argument)
{
    for (;;)
    {
        // Wait forever for ISR notification
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // ---- Button logic here ----
        // debounce
        //osDelay(20);
        vTaskDelay(20);
        //gpio_port_read(GPIO13);
        
        if (gpio_get(GPIOA, GPIO0))
        {
            // Button confirmed pressed
            // Toggle LED / send event / change state
        }
    }
}


void ButtonTask_Init(void)
{
    xTaskCreate(
        ButtonTask,
        "ButtonTask",
        256,
        NULL,
        //osPriorityNormal,
        configMAX_PRIORITIES - 1,
        &buttonTaskHandle
    );
}

TaskHandle_t ButtonTask_GetHandle(void)
{
    return buttonTaskHandle;
}
