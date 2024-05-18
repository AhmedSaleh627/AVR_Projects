#include "STD_Type.h"
#include "BITMATH.h"
#include "DIO_interface.h"
#include "SPI_interface.h"
#include "ADC_interface.h"
#include "GIE_interface.h"
#include "TWI_interface.h"
#include "LCD_interface.h"
#include "Keypad_interface.h"
#define F_CPU 16000000UL
#include "util/delay.h"


int main(void)
{
	SPI_Vid_Slave_Init();
	u8 loc=0;
	u8 count=0;
	DIO_Vid_Set_Pin_Dir(PORTD,PIN0,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTB,PIN5,OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTB,PIN4,INPUT);
	DIO_Vid_Set_Pin_Dir(PORTB,PIN6,INPUT);
	DIO_Vid_Set_Pin_Dir(PORTB,PIN7,INPUT);
	DIO_Vid_Set_Pin_Dir(PORTD,PIN7,INPUT);
	LCD_Vid_Init();
	KEYPAD_Vid_Init() ;
	u8 key=0xff ;
	u8 key2=0xff ;
	u8 i=0,j=0,temp1=0,d=0,d2=0,temp3=0;
	u64 temp2=0,temp4=0,password=0,password2=0;
	u8 flag=0;
	
	LCD_Send_String("SET PASSWORD: ");
	while (1)
	{
		
		
		/*Set PAssword*/
		while(1)
		{
			
			key2=KEYPAD_u8_Get_Key() ;
			d2=asc_to_int(key2);
			
			if(key2 == '1' || key2=='2' || key2=='3' || key2=='4' || key2=='5' || key2=='6'||key2=='7'||key2=='8'||key2=='9' || key2=='*'  )
			{
				if(key2=='*')
				{
					if(i<6)
					{
						CLR_Display();
						LCD_Vid_GOTOXY(0,0);
						LCD_Send_String("INVALID");
						LCD_Vid_GOTOXY(0,1);
						LCD_Send_String("MINIMUM 6 DIGITS!!");
						_delay_ms(800);
						CLR_Display();
						_delay_ms(300);
						LCD_Send_String("SET PASSWORD: ");
						if(temp2==0)
						{
							LCD_Vid_GOTOXY(0,1);
							LCD_Send_Number(temp1);
						}
						else
						{
							LCD_Vid_GOTOXY(0,1);
							LCD_Send_Number(temp2);
						}
						
					}
					else
					{
						_delay_ms(100);
						CLR_Display();
						LCD_Send_String("PASSWORD SET!!");
						_delay_ms(300);
						CLR_Display();
						_delay_ms(300);
						LCD_Send_String("CHECK PASSWORD: ");
						
						i=8;
						break;
					}
					
				}
				else{
					i++;
					switch (i){
						
						case 1:
						temp1=d2;
						LCD_Vid_GOTOXY(0,1);
						LCD_Send_Number(temp1);
						break;
						case 2:
						temp1=temp1*10+(d2);
						LCD_Vid_GOTOXY(0,1);
						LCD_Send_Number(temp1);
						break;
						case 3:
						temp2=temp1*10+(d2);
						LCD_Vid_GOTOXY(0,1);
						LCD_Send_Number(temp2);
						break;
						case 4:
						temp2=temp2*10+(d2);
						LCD_Vid_GOTOXY(0,1);
						LCD_Send_Number(temp2);
						break;
						case 5:
						temp2=temp2*10+(d2);
						LCD_Vid_GOTOXY(0,1);
						LCD_Send_Number(temp2);
						break;
						case 6:
						temp2=temp2*10+(d2);
						LCD_Vid_GOTOXY(0,1);
						LCD_Send_Number(temp2);
						break;
						case 7:
						temp2=temp2*10+(d2);
						LCD_Vid_GOTOXY(0,1);
						LCD_Send_Number(temp2);
						break;
						
					}
					password=temp2;
					
				}
				
				
				
			}
			
		}
		while(1)
		{
			key=KEYPAD_u8_Get_Key() ;
			d=asc_to_int(key);
			if(key == '1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6'||key=='7'||key=='8'||key=='9'  )
			{
				
				j++;
				switch (j){
					case 1:
					temp3=d;
					LCD_Vid_GOTOXY(0,1);
					LCD_Send_Number(temp3);
					break;
					case 2:
					temp3=temp3*10+(d);
					LCD_Vid_GOTOXY(0,1);
					LCD_Send_Number(temp3);
					break;
					case 3:
					temp4=temp3*10+(d);
					LCD_Vid_GOTOXY(0,1);
					LCD_Send_Number(temp4);
					break;
					case 4:
					temp4=temp4*10+(d);
					LCD_Vid_GOTOXY(0,1);
					LCD_Send_Number(temp4);
					break;
					case 5:
					temp4=temp4*10+(d);
					LCD_Vid_GOTOXY(0,1);
					LCD_Send_Number(temp4);
					break;
					case 6:
					temp4=temp4*10+(d);
					LCD_Vid_GOTOXY(0,1);
					LCD_Send_Number(temp4);
					break;
					case 7:
					temp4=temp4*10+(d);
					LCD_Vid_GOTOXY(0,1);
					LCD_Send_Number(temp4);
					break;
				}
				if(temp4==0)
				{
					password2=temp3;
				}
				else
				{
					password2=temp4;
				}
				
				
			}
			if(j>=7 || key=='*')
			{
				
				if(password2==password )
				{
					CLR_Display();
					LCD_Vid_GOTOXY(0,0);
					LCD_Send_String("CORRECT");
					LCD_Vid_GOTOXY(5,1);
					LCD_Send_String("PASSWORD!!!!");
					_delay_ms(400);
					CLR_Display();
					LCD_Vid_GOTOXY(0,0);
					LCD_Send_String("Temprature= ");
					while(1)
					{	
							
						loc=SPI_Vid_Slave_Recieve();
							count++;
							LCD_Vid_GOTOXY(count+10,0);
							LCD_Vid_Send_Data(loc);
							_delay_ms(400);
							if(count==2)
							{
								count=0;
								//CLR_Display();
							}
						
						
						
					}
					
					
				}
				else if(password2!=password)
				{
					flag++;
					if(flag>=3)
					{
						CLR_Display();
						LCD_Send_String("LIMIT REACHED!!!");
						DIO_Vid_Set_Pin_Val(PORTD,PIN4,HIGH);
						break;
					}
					else
					{
						CLR_Display();
						LCD_Send_String("WRONG PASSWORD!!");
						DIO_Vid_Set_Pin_Val(PORTD,PIN4,HIGH);
						_delay_ms(500);
						DIO_Vid_Set_Pin_Val(PORTD,PIN4,LOW);
						CLR_Display();
						LCD_Send_String("CHECK PASSWORD:");
						j=0;
						
					}
					
					
				}
				
			}
			
		}

		
	}
	
}

