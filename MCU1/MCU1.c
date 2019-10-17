/*
 * MCU1.c
 *
 *  Created on: Oct 15, 2019
 *      Author: Mohammed Nassar
 */

#include "micro_config.h"
#include "std_types.h"
#include "lcd.h"
#include "keypad.h"
#include "UART.h"
#include "PBUTTON.h"
#include "TIMER.h"

uint16 sec=0;

int main(void)
{
	uint8 SPEED_PLUS=0;
	uint8 SPEED_MINUS=0;
	uint8 speed_flag=1;
	DIO_init();
	UART_init();
	LCD_init();
	LCD_clearScreen();
	uint8 key=NA;
	uint8 speed=0;
	//uint8 key;
	//UART_init();
	LCD_displayStringRowColumn(0,0,"Enter speed MAX 255");
	LCD_displayStringRowColumn(1,0,"Press any key");
	LCD_displayStringRowColumn(2,0,"to Start");

	while(speed_flag)
	    {

		key = KeyPad_getPressedKey();
        LCD_clearScreen();
		if( (key <= 9) && (key >= 0) )
		{
			speed*=10;
			speed+=key;
			LCD_displayStringRowColumn(0,0,"Speed : ");
			LCD_intgerToString(speed); /* display the speed Entered*/
		}

		else
		{
			speed_flag=0;
		}


		_delay_ms(500); /* Press time */
	    }

	//LCD_goToRowColumn(3,0);
	LCD_clearScreen();
	UART_sendByte(speed);
	LCD_displayStringRowColumn(0,0,"Speed : ");
	LCD_intgerToString(speed);
	LCD_displayStringRowColumn(1,0,"Time : 0 Sec");

	TIMER_init();
	TIMER_start();

	while(1)
	{
		PBUTTON_getStatus(BUTTON1,&SPEED_PLUS);

		if (SPEED_PLUS==1)
		{
			speed+=1;
			//LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Speed : ");
			LCD_intgerToString(speed);
		}

		PBUTTON_getStatus(BUTTON2,&SPEED_MINUS);

		if (SPEED_MINUS==1)
		{
			speed-=1;
			//LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Speed : ");
			LCD_intgerToString(speed);
		}

		if (TIME_flag==1)
		{
			TIME_flag=0;
			sec+=1;
			UART_sendByte(speed);
			LCD_displayStringRowColumn(1,0,"Time : ");
			LCD_intgerToString(sec);
			LCD_displayString(" Sec");

		}


	}

    return 0;
}
