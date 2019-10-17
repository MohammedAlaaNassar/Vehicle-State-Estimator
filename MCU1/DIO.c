/*
 * DIO.c
 *
 *  Created on: Oct 17, 2019
 *      Author: Mohammed Nassar
 */


#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

#include "DIO.h"
#include "DIO_Pbcfg.h"


void DIO_init()
{
	uint8 loop_index = 0;
	if (NUM_OF_PINS <= MAX_NUM_OF_PINS)
	{
		for(;loop_index < NUM_OF_PINS; loop_index++)
		{
			DIO_cfg_list[loop_index].IS_init = INITIALIZED;
			switch(DIO_cfg_list[loop_index].PORT)
			{
			case PORT_A:
				if(DIO_cfg_list[loop_index].DIR == OUTPUT)
				{
					DDRA |=(1u<<DIO_cfg_list[loop_index].PIN);
					if (DIO_cfg_list[loop_index].VALUE == HIGH)
					{
						PORTA |=(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else if (DIO_cfg_list[loop_index].VALUE == LOW)
					{
						PORTA &=~(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else
					{
						DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
					}
				}
				else if(DIO_cfg_list[loop_index].DIR == INPUT)
				{
					DDRA &=~(1u<<DIO_cfg_list[loop_index].PIN);
					if (DIO_cfg_list[loop_index].PULL == PULLUP)
					{
						PORTA |=(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else if (DIO_cfg_list[loop_index].PULL == PULLDOWN )
					{
						PORTA &=~(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else
					{
						DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
					}
				}
				else
				{
					DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
				}
				break;
			case PORT_B:
				if(DIO_cfg_list[loop_index].DIR == OUTPUT)
				{
					DDRB |=(1u<<DIO_cfg_list[loop_index].PIN);
					if (DIO_cfg_list[loop_index].VALUE == HIGH)
					{
						PORTB |=(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else if (DIO_cfg_list[loop_index].VALUE == LOW)
					{
						PORTB &=~(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else
					{
						DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
					}
				}
				else if(DIO_cfg_list[loop_index].DIR == INPUT)
				{
					DDRB &=~(1u<<DIO_cfg_list[loop_index].PIN);
					if (DIO_cfg_list[loop_index].PULL == PULLUP)
					{
						PORTB |=(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else if (DIO_cfg_list[loop_index].PULL == PULLDOWN )
					{
						PORTB &=~(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else
					{
						DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
					}
				}
				else
				{
					DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
				}
				break;
			case PORT_C:
				if(DIO_cfg_list[loop_index].DIR == OUTPUT)
				{
					DDRC |=(1u<<DIO_cfg_list[loop_index].PIN);
					if (DIO_cfg_list[loop_index].VALUE == HIGH)
					{
						PORTC |=(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else if (DIO_cfg_list[loop_index].VALUE == LOW)
					{
						PORTC &=~(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else
					{
						DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
					}
				}
				else if(DIO_cfg_list[loop_index].DIR == INPUT)
				{
					DDRC &=~(1u<<DIO_cfg_list[loop_index].PIN);
					if (DIO_cfg_list[loop_index].PULL == PULLUP)
					{
						PORTC |=(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else if (DIO_cfg_list[loop_index].PULL == PULLDOWN )
					{
						PORTC &=~(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else
					{
						DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
					}
				}
				else
				{
					DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
				}
				break;
			case PORT_D:
				if(DIO_cfg_list[loop_index].DIR == OUTPUT)
				{
					DDRD |=(1u<<DIO_cfg_list[loop_index].PIN);
					if (DIO_cfg_list[loop_index].VALUE == HIGH)
					{
						PORTD |=(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else if (DIO_cfg_list[loop_index].VALUE == LOW)
					{
						PORTD &=~(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else
					{
						DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
					}
				}
				else if(DIO_cfg_list[loop_index].DIR == INPUT)
				{
					DDRD &=~(1u<<DIO_cfg_list[loop_index].PIN);
					if (DIO_cfg_list[loop_index].PULL == PULLUP)
					{
						PORTD |=(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else if (DIO_cfg_list[loop_index].PULL == PULLDOWN )
					{
						PORTD &=~(1u<<DIO_cfg_list[loop_index].PIN);
					}
					else
					{
						DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
					}
				}
				else
				{
					DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
				}
				break;
			default:
				DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
			}
		}
	}

	else
	{
		for (loop_index = 0; loop_index < NUM_OF_PINS ;loop_index++)
		{
			DIO_cfg_list[loop_index].IS_init = NOT_INITIALIZED;
		}

	}

}





/////****************************************************************************************************************////
/////****************************************************************************************************************////
/////****************************************************************************************************************////




void DIO_write(ECU device, uint8 value)
{

    if ( DIO_cfg_list[device].DIR == OUTPUT  && (value == HIGH || value == LOW))
    {
		switch(DIO_cfg_list[device].PORT)
        {
            case PORT_A:
				if (value == HIGH)
                {
                    PORTA |= (1u << DIO_cfg_list[device].PIN);
                }
                else
                {
					PORTA &= ~(1u << DIO_cfg_list[device].PIN);
                }
            break;

            case PORT_B:
            if (value == HIGH)
            {
                PORTB |= (1u << DIO_cfg_list[device].PIN);
            }
            else
            {
                PORTB &= ~(1u << DIO_cfg_list[device].PIN);
            }
            break;

            case PORT_C:
            if (value == HIGH)
            {
                PORTC |= (1u << DIO_cfg_list[device].PIN);
            }
            else
            {
                PORTC &= ~(1u << DIO_cfg_list[device].PIN);
            }
            break;

            case PORT_D:
            if (value == HIGH)
            {
                PORTD |= (1u << DIO_cfg_list[device].PIN);
            }
            else
            {
                PORTD &= ~(1u << DIO_cfg_list[device].PIN);
            }
            break;
        }

    }

}



/////****************************************************************************************************************////
/////****************************************************************************************************************////
/////****************************************************************************************************************////



void DIO_read(ECU device, uint8* result)
{

	if (DIO_cfg_list[device].IS_init == INITIALIZED)
	{
		switch(DIO_cfg_list[device].PORT)
		{
			case PORT_A:
			*result = (1u & (PINA >> DIO_cfg_list[device].PIN));
			break;

			case PORT_B:
			*result = (1u & (PINB >> DIO_cfg_list[device].PIN));
			break;

			case PORT_C:
			*result = (1u & (PINC >> DIO_cfg_list[device].PIN));
			break;

			case PORT_D:
			*result = (1u & (PIND >> DIO_cfg_list[device].PIN));
			break;
		}
	}
	else
	{
		*result = 0x00;
	}

}


























