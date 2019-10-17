/*
 * DIO.h
 *
 *  Created on: Oct 17, 2019
 *      Author: Mohammed
 */

#ifndef DIO_H_
#define DIO_H_

#include "DIO_cfg.h"


#define MAX_NUM_OF_PINS	(uint8)32

typedef enum {BUTTON1,BUTTON2,NUM_OF_PINS} ECU;

typedef struct
{
	uint8 PORT;
	uint8 PIN;
	uint8 DIR;
	uint8 VALUE;
	uint8 PULL;
	uint8 IS_init;
}DIO_cfg;

extern void DIO_init(void);
extern void DIO_read(ECU,uint8*);
extern void DIO_write(ECU,uint8);

#endif /* DIO_H_ */
