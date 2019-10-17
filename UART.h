/*
 * UART.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Mohammed
 */

#ifndef UART_H_
#define UART_H_


#include "UART_cfg.h"

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


extern void UART_init(void);
extern void UART_sendByte(const uint8);
extern void UART_recieveByte(uint8 *);





#endif /* UART_H_ */
