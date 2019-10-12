/*
 * UART_cnfg.h
 *
 *  Created on: Oct 12, 2019
 *      Author: Mohammed
 */

#ifndef UART_CFG_H_
#define UART_CFG_H_

#include "std_types.h"

/* USART MODE */
#define ASYNCHRONOUS  1
#define SYNCHRONOUS   0

/* COMMUNICATION MODEL */
#define P2P           2
#define MASTER        1
#define SLAVE         0

/*  DATA SIZE  */
#define NINE_BITS     4
#define EIGHT_BITS    3
#define SEVEN_BITS    2
#define SIX_BITS      1
#define FIVE_BITS     0

/* PARITY */
#define EVEN          2
#define ODD           1
#define DISABLED      0

/*  STOP PATTERN  */
#define TWO_BITS      1
#define BIT           0

/* TRANSMISSION SPEED */
#define DOUBLE_SPEED  1
#define NORMAL_SPEED  0

/*  BAUD RATE  */
#define USART_BAUDRATE 9600

/* INTERRUPT */
#define INTERRUPT     1
#define NO_INTERRUPT  0

/*  CLK EDGE  */
#define FALLING       1
#define RISING        0

/* INITIALIZATION	 */
#define INITIALIZED			1
#define NOT_INITIALIZED		0




typedef struct
{
	uint8 USART_mode;
	uint8 communication_model;
	uint8 data_size;
	uint8 parity;
	uint8 stop_pattern;
	uint8 tarnsmission_speed;
	uint32 baud_rate;
	uint8 interrupt;
	uint8 clk_edge;
	uint8 IS_init;
} UART_cnfg_t ;

#endif /* UART_CFG_H_ */
