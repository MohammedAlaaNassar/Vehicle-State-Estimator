/*
 * UART.h
 *
 *  Created on: Oct 11, 2019
 *      Author: Mohammed
 */

#ifndef UART_H_
#define UART_H_

#include "UART_Pbcfg.h"
#include "UART_cfg.h"

extern void UART_init(void);
extern void UART_sendByte(const uint8);
extern void UART_recieveByte(uint8 *);





#endif /* UART_H_ */
