/*
 * PBUTTON.c
 *
 *  Created on: Oct 17, 2019
 *      Author: Mohammed Nassar
 */



#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "PBUTTON.h"

//void INT0_Init(void)
//{
//	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
//	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
//	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
//	MCUCR |= (1<<ISC00) | (1<<ISC01);   // Trigger INT0 with the raising edge
//	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
//}
//
//void INT1_Init(void)
//{
//	SREG  &= ~(1<<7);      // Disable interrupts by clearing I-bit
//	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
//	PORTD |= (1<<PD3);     // Enable the internal pull up resistor at PD3 pin
//	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
//	MCUCR |= (1<<ISC10) | (1<<ISC11);
//	SREG  |= (1<<7);       // Enable interrupts by setting I-bit
//}
//
//ISR(INT0_vect)
//{
//	speed+= 1;
//}
//
//ISR(INT1_vect)
//{
//	print_flag = 1;
//}

void PBUTTON_getStatus(ECU BUTTON,uint8* Status)
{

	DIO_read(BUTTON,Status);

	_delay_ms(100);  // debouncing

DIO_read(BUTTON,Status);

}
