#include "freertos/FreeRTOSConfig.h"
#include "freertos/include/FreeRTOS.h"
#include "freertos/include/task.h"
#include "LIB/BITMATH.h"
#include "LIB/STD_Type.h"
#include "MCAL/UART/UART_Interface.h"
#include "MCAL/DIO/DIO_interface.h"
#define F_CPU 16000000


void LED_0(void* copy_pvParameter);
void Switch_0(void* copy_pvParameter);

static u8 flag=0;


int main(void) {
	
	DIO_Vid_Set_Pin_Dir(PORTC,PIN2,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTB,PIN0,INPUT);
	
	xTaskCreate(&LED_0,(const char*)"Task_1",100,NULL,1,NULL);
	xTaskCreate(&Switch_0,(const char*)"Task_2",100,NULL,2,NULL);

	vTaskStartScheduler();
	
	while (1) 
	{
		
	}
}

void LED_0(void* copy_pvParameter)
{
	
	TickType_t xLastWakeTime= xTaskGetTickCount();
	while(1)
	{
		if(flag==1)
		{
			DIO_Vid_Toggle_Pin_Val(PORTC,PIN2);
			flag=0;
		}
		
	xTaskDelayUntil(&xLastWakeTime,200);
//	xTaskDelayUntil(&xLastWakeTime,pdMS_TO_TICKS(3000));
	
	}
	
}
void Switch_0 (void* copy_pvParameter)
{	
	TickType_t xLastWakeTime= xTaskGetTickCount();
	u8 Loc_State;
	while(1)
	{
		vTaskDelay(100);
		Loc_State=DIO_u8_Get_Pin_Val(PORTB,PIN0);
		if(Loc_State==1)
		{
			flag=1;
		}

	}
	//xTaskDelayUntil(&xLastWakeTime,200);
}
