#include "freertos/FreeRTOSConfig.h"
#include "freertos/include/FreeRTOS.h"
#include "freertos/include/task.h"
#include "freertos/include/queue.h"
#include "LIB/STD_Type.h"
#include "LIB/BITMATH.h"
#include "MCAL/UART/UART_Interface.h"
#include <avr/io.h>

void task1(void * parameter);
void task2(void * parameter);
void recieve(void * parameter);
u8 data_1='A';
u8 data_2='B';
xQueueHandle queue_handler=NULL;
int main(void) {

	UART_Vid_Init();
	TaskHandle_t task1_handler = NULL;
	TaskHandle_t task2_handler = NULL;
	TaskHandle_t task3_handler = NULL;
	
	
	// Create Task1
	xTaskCreate(task1,        // TaskCode
	"Send_1",  // PC Name
	100,           // stack depth
	&data_1,          // Parameter
	1,             // Priority Level
	&task1_handler);// Handler
	
	
	// Create Task2
	xTaskCreate(task2,        // TaskCode
	"Send_2",  // PC Name
	100,           // stack depth
	&data_2,          // Parameter
	1,             // Priority Level
	&task2_handler);// Handler
	
	xTaskCreate(recieve,        // TaskCode
	"recieve",  // PC Name
	100,           // stack depth
	NULL,          // Parameter
	2,             // Priority Level
	&task3_handler);// Handler

	// Create Queue
	queue_handler=xQueueCreate(1,sizeof(unsigned char));
	
	// Start Scheduler.....
	vTaskStartScheduler();
	while (1) {
	}
}

void task1(void * parameter) {
	// init
	
	while (1) {
		
		xQueueSendToBack(queue_handler,parameter,10);
		
	}
	vTaskDelete(NULL);
	
}
void task2(void * parameter) {
	while (1) {
		xQueueSendToBack(queue_handler,parameter,10);
		
	}
	vTaskDelete(NULL);
	
}
void recieve(void * parameter) {
	u8 loc_var=0;
	
	while (1) {
		
		xQueueReceive(queue_handler,&loc_var,10);
		UART_Vid_Send(loc_var);
	
		
	}
	vTaskDelete(NULL);
	
}
