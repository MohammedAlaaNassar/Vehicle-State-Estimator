/*
 * TIMER.h
 *
 *  Created on: Oct 13, 2019
 *      Author: Mohammed
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "TIMER_cfg.h"

typedef struct
{
	uint8 TIMER_ID;
	uint8 WGM_Mode;
	uint8 COM_mode;
	uint8 prescaler;
	uint8 interrupt;
	uint8 IS_init;
} TIMER_cnfg_t ;

#include "TIMER_Pbcfg.h"

extern uint8 TIME_flag;
extern void TIMER_init(void);
extern void TIMER_start(void);
extern void TIMER_stop(void);

#endif /* TIMER_H_ */
