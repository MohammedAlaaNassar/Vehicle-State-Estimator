/*
 * UART.c
 *
 *  Created on: Oct 15, 2019
 *      Author: Mohammed
 */


#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

#include "UART.h"
#include "UART_Pbcfg.h"


void UART_init(void){

	if (UART.IS_init == NOT_INITIALIZED )
	{


		UART.IS_init= INITIALIZED ;

		SET_BIT(UCSRC,URSEL); // URSEL= 1 The URSEL must be one when writing the UCSRC

		/* USART MODE */
		switch(UART.USART_mode)
		{
		case SYNCHRONOUS  : SET_BIT(UCSRC,UMSEL); // SYNCHRONOUS
		break;
		case ASYNCHRONOUS : CLEAR_BIT(UCSRC,UMSEL); // ASYNCHRONOUS
		break;
		default: UART.IS_init= NOT_INITIALIZED ;
		return ;
		}

		/* COMMUNICATION MODEL */
		switch(UART.communication_model)
		{
		case SLAVE : SET_BIT(UCSRB,RXEN); // Receiver Enable
		break;
		case MASTER : SET_BIT(UCSRB,TXEN); // Transmitter Enable
		break;
		case P2P : SET_BIT(UCSRB,TXEN); // Transmitter Enable
		SET_BIT(UCSRB,RXEN); // Receiver Enable
		break;
		default: UART.IS_init= NOT_INITIALIZED ;
		return ;
		}

		/*  DATA SIZE  */
		switch(UART.data_size)
		{
		case FIVE_BITS : UCSRC &= ~((1<<UCSZ2) & (1<<UCSZ1) & (1<<UCSZ0) ); // UCSZ2=0 UCSZ1=0 UCSZ0=0
		break;
		case SIX_BITS : UCSRC &= ~((1<<UCSZ2) & (1<<UCSZ1)); // UCSZ2=0 UCSZ1=0
		UCSRC |=  (1<<UCSZ0) ; // UCSZ0=1
		break;
		case SEVEN_BITS : UCSRC &= ~((1<<UCSZ2) & (1<<UCSZ0)); // UCSZ2=0 UCSZ0=0
		UCSRC |=  (1<<UCSZ1) ; // UCSZ1=1
		break;
		case EIGHT_BITS : UCSRC &= ~ (1<<UCSZ2) ; // UCSZ2=0
		UCSRC |=  (1<<UCSZ1) | (1<<UCSZ0) ; // UCSZ1=1 UCSZ0=1
		break;
		case NINE_BITS : UCSRC |= ~((1<<UCSZ2) | (1<<UCSZ1) | (1<<UCSZ0) ); //UCSZ2=1 UCSZ1=1 UCSZ0=1
		break;
		default: UART.IS_init= NOT_INITIALIZED ;
		return ;
		}

		/* PARITY */
		switch(UART.parity)
		{
		case DISABLED : UCSRC &= ~( (1<<UPM1) & (1<<UPM0) );  // UPM1=O UPM0=O ODD DISABLED
		break;
		case ODD : UCSRC |=  (1<<UPM1) | (1<<UPM0) ; // UPM1=1 UPM0=1 ODD PARITY
		break;
		case EVEN : UCSRC &= (1<<UPM0); // UPM0=0 EVEN PARITY
		UCSRC |=  (1<<UPM1); // UPM1=1 EVEN PARITY
		break;
		default: UART.IS_init= NOT_INITIALIZED ;
		return ;
		}

		/*  STOP PATTERN  */
		switch(UART.stop_pattern)
		{
		case BIT : CLEAR_BIT(UCSRC,USBS); // STOP BIT
		break;
		case TWO_BITS : SET_BIT(UCSRC,USBS); // 2 STOP
		break;
		default: UART.IS_init= NOT_INITIALIZED ;
		return ;
		}


		/* TRANSMISSION SPEED */
		switch(UART.tarnsmission_speed)
		{
		case DOUBLE_SPEED : SET_BIT(UCSRA,U2X); // DOUBLE SPEED
		break;
		case NORMAL_SPEED :
		case NA : CLEAR_BIT(UCSRA,U2X); // NORMAL SPEED OR SYNCHRONOUS
		break;
		default: UART.IS_init= NOT_INITIALIZED ;
		return ;
		}

		/*  BAUD RATE  */

		/* First 8 bits from the BAUD_PPULLCALE inside UBRRL and last 4 bits in UBRRH*/
		uint32 BAUD_PPULLCALE = (((F_CPU / (USART_BAUDRATE * 8UL))) - 1);
		UBRRH = BAUD_PPULLCALE>>8;
		UBRRL = BAUD_PPULLCALE;


		/* INTERRUPT */
		switch(UART.interrupt)
		{

		case  POOLING : CLEAR_BIT(UCSRB,RXCIE); // RX COMPLETE DISABLED
		                     CLEAR_BIT(UCSRB,TXCIE); // TX COMPLETE DISABLED
		break;

		case INTERRUPT : {
			sei();  // Global INTERRUPT Enable
			if (UART.communication_model == SLAVE )
			{
				SET_BIT(UCSRB,RXCIE); // RX COMPLETE ENABLED
			}
			else if (UART.communication_model== MASTER )
			{
				SET_BIT(UCSRB,TXCIE); // TX COMPLETE ENABLED
			}
			else if (UART.communication_model== P2P )
			{
				SET_BIT(UCSRB,RXCIE); // RX COMPLETE ENABLED
				SET_BIT(UCSRB,TXCIE); // TX COMPLETE ENABLED
			}
			else
			{
				UART.IS_init= NOT_INITIALIZED ;
			}

			break;
		}

		default: UART.IS_init= NOT_INITIALIZED ;
		return ;
		}

		/*  CLK EDGE  */
		switch(UART.clk_edge)
		{
		case RISING :
		case NA : CLEAR_BIT(UCSRC,UCPOL); // RISING XCK Edge OR Asynchronous
		break;
		case FALLING : SET_BIT(UCSRC,UCPOL); // FALLING XCK Edge
		break;
		default: UART.IS_init= NOT_INITIALIZED ;
		return ;
		}

	}
}



void UART_sendByte(const uint8 data){

	if ( (UART.IS_init==INITIALIZED) && (UART.interrupt== POOLING ) )
	{

		while(BIT_IS_CLEAR(UCSRA,UDRE)){} // UDRE flag is set when the TX buffer (UDR) is empty

		UDR = data; ///Put the required data in the UDR register

	}
}





void UART_recieveByte(uint8 * data){

	if ( (UART.IS_init==INITIALIZED) && (UART.interrupt== POOLING ) )
	{

		while(BIT_IS_CLEAR(UCSRA,RXC)){} //RXC flag is set when the UART receive data

		*data=UDR; // Read the received data from  (UDR)


	}
}

/*

ISR(USART_RXC_vect)
{
	(*rx)();
}


ISR(USART_TXC_vect)
{
	(*tx)();
}

*/


