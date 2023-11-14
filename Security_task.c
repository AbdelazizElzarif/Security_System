/*
 * Security_task.c
 *
 * Created: 11/11/2023 12:52:54 PM
 *  Author: ENG-ABDELAZIZ
 */ 
#include "StdTupes.h"
#include "Security_tssk.h"
#include "LCD_Interface.h"
#include "UART_Service1.h"
#include "DIO_interface.h"
#include "Timers.h"
#include "LCD_Interface.h"
u32 key=0;

u8 flag_security=0;
u8 message[50]={0};
Bool_t r=0; 
u32 random_num_Incr_ecu;
u32 random_num;
u32 random_num_Incr_app;
static task_t tasks[NofTasks]={{(u8*)"3101AA00",LedOnTask},
                              {(u8*)"2701",Security_Acess}};
								 
void Security_Init(void)
{
	UART_Init();
	DIO_InintPins();
	LCD_Init();
	Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
	LCD_Clear();
	
}		
void Security_Runabble(void)
{
	u8 i=0,F=0;
	UART_ReceiveString(message);
	for(i=0;i<NofTasks;i++)
	{
		r=sring_Cmp(message,tasks[i].str);
		if(r==TRUE)
		{
			message,tasks[i].fptr();
			F=1;
			break;
		}
	}
	if(F==0)
	{
		UART_SendString("7F2735");
	}
}						 
void LedOnTask(void)
{
	if(flag_security==1)
	{
		LCD_Clear();
		LCD_WriteString("Enter RESULT OF ALGORIZM");
		UART_ReceiveString(message);
		for(u8 i=0;message[i];i++)
		{
			key=(key*10)+(message[i]-'0');
		}
		
		u32 random_num_Incr_app=key;
		if(random_num_Incr_app==random_num_Incr_ecu)
		{
			UART_SendString("710IAA00");
			DIO_WritPin(LED,HIGH);
			LCD_Clear();
			LCD_WriteString("valid operation");
		}
		else
		{
			UART_SendString("7F2735");
			key=0;
		}
		
		
	}
	else
	{
		UART_SendString("NRCF3135");
	}
	
}

Bool_t sring_Cmp(u8*str1,u8*str2)
{
	Bool_t r=TRUE;
	u8 i;
	for(i=0;str1[i]||str2[i];i++)
	{
		if(str1[i]!=str2[i])
		{
			r=FALSE;
			break;
		}
	}
	return r;
}
void Security_Acess(void)
{
	u32 temp_random=0;
	u8 str[10]={0};
	random_num=TIMER1_READ_COUNTER()*((u32)6000000);
	random_num_Incr_ecu=random_num^TKEY;
	UART_SendString("6702 ");
	temp_random=random_num;
	s8 i=0;
	while(temp_random)
	{
		
		str[i]=temp_random%10+'0';
		temp_random/=10;
		i++;
	}
	str[i]=0;
	string_reverse(str);
	UART_SendString(str);
	
	
	
	
	flag_security=1;
	
}
void string_reverse(char *str)
{
	int length;
	length=string_length(str);
	length--;
	int i;
	for(i=0;i<=length;i++,length--)
	{
		char temp;
		temp=str[i];
		str[i]=str[length];
		str[length]=temp;
		
	}
	
	

}

int string_length(char *str)
{
	int i;
	for(i=0;str[i];i++);
	
	
	return i;
}