/*
 * UART_Pbcfg.c
 *
 *  Created on: Oct 12, 2019
 *      Author: Mohammed
 */


#include "UART_Pbcfg.h"



//UART_cnfg_t UART = {USART MODE,COMMUNICATION MODEL,DATA SIZE,PARITY,STOP PATTERN,TRANSMISSION SPEED,BAUD RATE,INTERRUPT,CLK EDGE,INITIALIZATION};
UART_cnfg_t UART = {ASYNCHRONOUS,P2P,EIGHT_BITS,DISABLED,BIT,DOUBLE_SPEED,USART_BAUDRATE,POOLING,NA,NOT_INITIALIZED};
