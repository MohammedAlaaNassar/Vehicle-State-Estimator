/*
 * DIO_cfg.h
 *
 *  Created on: Oct 17, 2019
 *      Author: SAMSUNG
 */

#ifndef DIO_CFG_H_
#define DIO_CFG_H_



#include "std_types.h"

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define OUTPUT 1
#define INPUT 0

#ifndef HIGH
#define HIGH 1
#endif
#ifndef LOW
#define LOW	 0
#endif

#define PULLUP 1
#define PULLDOWN 0

#define INITIALIZED 1
#define NOT_INITIALIZED 0

#define NA 0xff


#endif /* DIO_CFG_H_ */
