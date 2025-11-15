#include "USB.h"
void usbTask(void* args) ;
int main(void)
{
	// Blue Pill
	rcc_clock_setup_in_hse_8mhz_out_72mhz();

	// Initialize Builtin LED
	rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
	gpio_set(GPIOC, GPIO13); // turn led off at start

	xTaskCreate(usbTask, "usb", 200, NULL, configMAX_PRIORITIES - 1, NULL);

	// Start FreeRTOS
	vTaskStartScheduler();

	for (;;);

	return 0;
}

/// @brief blink if stack overflow
void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName) {
	for (;;) {
		gpio_toggle(GPIOC, GPIO13);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}