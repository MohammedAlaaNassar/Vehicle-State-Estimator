
#include "uart.h"
#include "lcd.h"
#include "DIO.h"
#include "micro_config.h"
#include "std_types.h"
#include "std.h"
#include "ExtInter.h"
#include <avr/interrupt.h>


void update_distance();
void print_distance();

void INT0_Init(void);
void INT1_Init(void);




uint8 measurment_flag = 0; 
uint8 print_flag = 0;

uint32 current_time = 0; 
uint32 speed = 0;
uint32 acc_distance = 0; 

uint32 temp_current_time = 0;
uint8 temp_speed = 0;
uint32 temp_acc_distance = 0;


int main(void)
{
	LCD_init();
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Time=");
	LCD_displayStringRowColumn(0,7,"speed=");
	LCD_displayStringRowColumn(1,0,"dis=");

	uint8 temp; 
	DIO_init();
	UART_init();
	
	INT0_Init();
	INT1_Init();

	DDRB = 0xff;
    while(1)
    {

		temp_speed = UART_recieveByte();
		if(current_time <= 9)
		{
			LCD_displayStringRowColumn(0,6," ");
		}
		LCD_goToRowColumn(0,5);
		LCD_intgerToString(current_time);
		current_time++;
		update_distance();
		print_distance();
    }
}

void update_distance()
{
	if(measurment_flag == 1)
	{
		acc_distance += speed; 
		speed = temp_speed;
		//current_time = temp_current_time;
	}
}

void print_distance()
{
	if(print_flag && measurment_flag)
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Time=");
		LCD_displayStringRowColumn(0,7,"speed=");
		LCD_displayStringRowColumn(1,0,"dis=");
		LCD_goToRowColumn(0,5);
		LCD_intgerToString(current_time);
		LCD_goToRowColumn(0,14);
		LCD_intgerToString(speed);
		LCD_goToRowColumn(1,4);
		LCD_intgerToString(acc_distance);
		measurment_flag = 0;
		print_flag = 0;
		current_time = 0;
		speed = 0;
		acc_distance = 0;	
	}
}

void INT0_Init(void)
{
	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
	MCUCR |= (1<<ISC00) | (1<<ISC01);   // Trigger INT0 with the raising edge
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}

void INT1_Init(void)
{
	SREG  &= ~(1<<7);      // Disable interrupts by clearing I-bit
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	//PORTD |= (1<<PD3);     // Enable the internal pull up resistor at PD3 pin
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
	// Trigger INT1 with the falling edge
	MCUCR |= (1<<ISC10) | (1<<ISC11);
	SREG  |= (1<<7);       // Enable interrupts by setting I-bit
}

ISR(INT0_vect)
{
	measurment_flag = 1;
	LCD_goToRowColumn(0,5);
	LCD_intgerToString(current_time);
	LCD_goToRowColumn(0,14);
	LCD_intgerToString(speed);
	LCD_goToRowColumn(1,4);
	LCD_intgerToString(acc_distance);
}

ISR(INT1_vect)
{
	print_flag = 1;
}



		/*DIO_read(measurment_switch, &temp);
		if (temp)
		{
			measurment_flag = 1;
		}*/
		
		/*DIO_read(print_switch, &temp);
		if (temp)
		{
			print_flag = 1;
		}*/
		
/*
void raise_measurement_flag();
void raise_print_flag();
void raise_measurement_flag()
{
	measurment_flag = 1;
	DIO_write(led_flag, HIGH);
}

void raise_print_flag()
{
	print_flag = 1;
}*/