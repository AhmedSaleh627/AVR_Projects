#include "freertos/FreeRTOSConfig.h"
#include "freertos/include/FreeRTOS.h"
#include "freertos/include/task.h"
#include "LIB/BITMATH.h"
#include "LIB/STD_Type.h"
#include "MCAL/UART/UART_Interface.h"
#include "MCAL/DIO/DIO_interface.h"
#define F_CPU 16000000


void LED_0(void* copy_pvParameter);
void LED_1(void* copy_pvParameter);
void LED_2(void* copy_pvParameter);
void Buzzer(void* copy_pvParameter);



int main(void) {
	
	DIO_Vid_Set_Pin_Dir(PORTC,PIN2,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTC,PIN7,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTD,PIN3,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTA,PIN3,OUTPUT);
	
	xTaskCreate(&LED_0,(const char*)"Task_1",100,NULL,0,NULL);
	xTaskCreate(&LED_1,(const char*)"Task_1",100,NULL,0,NULL);
	xTaskCreate(&LED_2,(const char*)"Task_1",100,NULL,0,NULL);
	xTaskCreate(&Buzzer,(const char*)"Task_1",100,NULL,0,NULL);
	
	vTaskStartScheduler();
	
	while (1) 
	{
		
	}
}

void LED_0(void* copy_pvParameter)
{
	while(1)
	{
		DIO_Vid_Toggle_Pin_Val(PORTC,PIN2);
		vTaskDelay(500);
	}
	
}
void LED_1(void* copy_pvParameter)
{
	while(1)
	{
		DIO_Vid_Toggle_Pin_Val(PORTC,PIN7);
		vTaskDelay(1000);
	}
	
}
void LED_2(void* copy_pvParameter)
{
	while(1)
	{
		DIO_Vid_Toggle_Pin_Val(PORTD,PIN3);
		vTaskDelay(2000);
	}
	
}
void Buzzer(void* copy_pvParameter)
{
	while(1)
	{
		DIO_Vid_Toggle_Pin_Val(PORTA,PIN3);
		vTaskDelay(500);
	}
	
}