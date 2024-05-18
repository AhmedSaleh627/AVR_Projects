#include "freertos/FreeRTOSConfig.h"
#include "freertos/include/FreeRTOS.h"
#include "freertos/include/task.h"
#include "freertos/include/queue.h"
#include "LIB/STD_Type.h"
#include "LIB/BITMATH.h"
#include "MCAL/UART/UART_Interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "freertos/include/semphr.h"
#include <avr/io.h>

void task1(void *parameter);
void task2(void *parameter);
void recieve(void *parameter);

u8 data=0;

xSemaphoreHandle semaphorehandler=NULL;
int main(void) {

	UART_Vid_Init();
	TaskHandle_t task1_handler = NULL;
	TaskHandle_t task2_handler = NULL;
	// Create Task1
	xTaskCreate(task1, "Send_1", 100, NULL, 1, &task1_handler);

	// Create Task2
	xTaskCreate(task2, "Send_2", 100, NULL, 2, &task2_handler);

	semaphorehandler= xSemaphoreCreateBinary();

	// Start Scheduler.....
	vTaskStartScheduler();

	while (1) {
	}
}

void task1(void *parameter) {
	while (1) {
		//	xQueueSendToBack(queue_handler, parameter, 10);
		if(xSemaphoreTake(semaphorehandler,10)==0)
		{
			data='A';
			UART_Vid_Send(data);
			UART_Vid_Send('\r');
			xSemaphoreGive(semaphorehandler);
		}
		
	}
	
}

void task2(void *parameter) {
	while (1) {
		//	xQueueSendToBack(queue_handler, parameter, 10);
		if(xSemaphoreTake(semaphorehandler,10)==0)
		{
			data='B';
			UART_Vid_Send(data);
			UART_Vid_Send('\r');
			xSemaphoreGive(semaphorehandler);
		}
		
	}
}
