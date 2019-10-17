/*
 * TIMER.c
 *
 *  Created on: Oct 13, 2019
 *      Author: Mohammed
 */

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "TIMER.h"
#include "lcd.h"

static uint16 num=0;
uint8 TIME_flag=0;

void TIMER_interrupt(void);

//TIMER_cnfg_t TIMER = {TIMER_ID,WGM_Mode,COM_mode,Prescaler,interrupt,INITIALIZATION};
//TIMER_cnfg_t TIMER = {TIMER0,NORMAL_MODE,NORMAL,PPULLCALER0,INTERRUPT,NOT_INITIALIZED};


void TIMER_init(void){

	if( TIMER.IS_init == NOT_INITIALIZED )
	{

		TIMER.IS_init = INITIALIZED;

		switch(TIMER.WGM_Mode)
		{   /********************  WGM mode    ********************/

		case NORMAL_MODE:{

			switch(TIMER.TIMER_ID)
			{

			case TIMER0:   /*********** TIMER0 NORMAL_MODE *********/
			{
				TCNT0 = 0; //timer initial value
				TCCR0 &=  ~ ( (1u<<WGM01) | (1u<<WGM00) );	// NORMAL_MODE WGM01=0 & WGM00=0
				TCCR0 = (1<<FOC0); //Non PWM mode
				//  END OF TIMER0 NORMAL_MODE
			}
			break;

			case TIMER2: /*********** TIMER2 NORMAL_MODE *********/
			{
				TCNT2 = 0; //timer initial value
				TCCR2 &=  ~ ( (1u<<WGM21) | (1u<<WGM20) );	// NORMAL_MODE WGM21=0 & WGM20=0
				TCCR2 = (1<<FOC2); //Non PWM mode
				// END OF TIMER2 NORMAL_MODE
			}
			break;

			case TIMER1:/*********** TIMER1 NORMAL_MODE *********/
			{
				TCNT1H=0;
				TCNT1L=0;  //TCNT1=0;
				TCCR1A &= (~(1<<WGM10) & ~(1<<WGM11));
				TCCR1B &= (~(1<<WGM13) & ~(1<<WGM12));
				// END OF TIMER1 NORMAL_MODE
			}
			break;

			default:   TIMER.IS_init = NOT_INITIALIZED;
			break;

			// END OF SWITCH TIMER ID
			}
		}
		// END OF NORMAL_MODE
		break;


		case CTC_MODE:{

			switch(TIMER.TIMER_ID)
			{

			case TIMER0:/*********** TIMER0 CTC MODE *********/
			{
				TCNT0 = 0; //timer initial value
				TCCR0 |= (1u<<WGM01) ; // CTC WGM01=1
				TCCR0 &= ( ~ (1u<<WGM00) );  // CTC  WGM00=0
				TCCR0 = (1<<FOC0); //Non PWM mode
				OCR0 = (uint8) 250;
				// END OF TIMER0 CTC_MODE
			}
			break;

			case TIMER2:/*********** TIMER2 CTC MODE *********/
			{
				TCNT2 = 0; //timer initial value
				TCCR2 |= (1u<<WGM21) ; // CTC WGM21=1
				TCCR2 &= ( ~ (1u<<WGM20) );  // CTC  WGM20=0
				TCCR2 = (1<<FOC2); //Non PWM mode
				OCR2 = (uint8) 250;
				// END OF TIMER2 CTC_MODE
			}
			break;

			case TIMER1:/*********** TIMER1 CTC MODE *********/
			{
				TCNT1H=0;
				TCNT1L=0;  //TCNT1=0;
				TCCR1A &= (~(1<<WGM10)) & (~(1<<WGM11));
				TCCR1B |= (1<<WGM12);
				TCCR1B &= (~(1<<WGM13));
				OCR1A = (uint16) 250;
				// END OF TIMER1 CTC_MODE
			}
			break;

			default:   TIMER.IS_init = NOT_INITIALIZED;
			break;

			// END OF SWITCH TIMER ID
			}

		}
		// END OF CTC_MODE
		break;



		default:   TIMER.IS_init = NOT_INITIALIZED;
		break;

		/******************** END OF SWITCH WGM mode    ********************/
		}


		/////****************************************************************************************************************////


		switch(TIMER.COM_mode)
		{   /********************  COM mode    ********************/

		case NORMAL:
		{  /***********   NORMAL  *********/

			switch(TIMER.TIMER_ID)
			{

			case TIMER0:   /***********   TIMER0 NORMAL    *********/
			{
				TCCR0 &= ~((1u << COM01) | (1u << COM00));// NORMAL COM01=0 & COM00=0
				//  END OF TIMER0 NORMAL
			}
			break;

			case TIMER2: /***********   TIMER2 NORMAL  *********/
			{
				TCCR2 &=  ~ ( (1u<<COM21) | (1u<<COM20) );	// NORMAL COM21=0 & COM20=0
				// END OF TIMER2 NORMAL
			}
			break;

			case TIMER1:/*********** TIMER1 NORMAL  *********/
			{
				TCCR1A &= (~(1<<COM1A1)) & (~(1<<COM1A0));
				// END OF TIMER1 NORMAL
			}
			break;

			default:   TIMER.IS_init = NOT_INITIALIZED;
			break;

			// END OF SWITCH TIMER ID
			}
		}
		// END OF NORMAL
		break;


		case TOGGLE:
		{ /*********** TOGGLE *********/

			switch(TIMER.TIMER_ID)
			{

			case TIMER0:/*********** TIMER0 TOGGLE *********/
			{
				TCCR0 &= (~(1u << COM01)); // TOGGLE COM01=0
				TCCR0 |= (1u << COM00);  // TOGGLE  COM00=1
				// END OF TIMER0 TOGGLE
			}
			break;

			case TIMER2:/*********** TIMER2 TOGGLE *********/
			{
				TCCR2 &= ( ~(1u<<COM21) ); // TOGGLE COM21=0
				TCCR2 |=  (1u<<COM20);  // TOGGLE  COM20=1
				// END OF TIMER2 TOGGLE
			}
			break;

			case TIMER1:/*********** TIMER1 TOGGLE *********/
			{
				TCCR1A &= (~(1<<COM1A1));
				TCCR1A |= (1<<COM1A0);
				// END OF TIMER1 TOGGLE
			}
			break;

			default:   TIMER.IS_init = NOT_INITIALIZED;
			break;

			// END OF SWITCH TIMER ID
			}

		}
		// END OF TOGGLE
		break;


		case CLEAR:
		{ /*********** CLEAR *********/

			switch(TIMER.TIMER_ID)
			{

			case TIMER0:/*********** TIMER0 CLEAR *********/
			{
				TCCR0 |= (1u << COM01); // CLEAR COM01=1
				TCCR0 &= (~(1u << COM00));  // CLEAR  COM00=0
				// END OF TIMER0 CLEAR
			}
			break;

			case TIMER2:/*********** TIMER2 CLEAR *********/
			{
				TCCR2 |= (1u<<COM21) ; // CLEAR COM21=1
				TCCR2 &= ( ~ (1u<<COM20) );  // CLEAR  COM20=0
				// END OF TIMER2 CLEAR
			}
			break;

			case TIMER1:/*********** TIMER1 CLEAR *********/
			{
				TCCR1A |= (1<<COM1A0);
				TCCR1A &= (~(1<<COM1A1));
				// END OF TIMER1 CLEAR
			}
			break;

			default:   TIMER.IS_init = NOT_INITIALIZED;
			break;

			// END OF SWITCH TIMER ID
			}

		}
		// END OF CLEAR
		break;



		case SET:
		{ /*********** SET *********/

			switch(TIMER.TIMER_ID)
			{

			case TIMER0:/*********** TIMER0 SET *********/
			{
				TCCR0 |= ((1u << COM01) | (1u << COM00)); // SET COM01=1 & COM00=1
				// END OF TIMER0 SET
			}
			break;

			case TIMER2:/*********** TIMER2 SET *********/
			{
				TCCR2 |= ( (1u<<COM21) | (1u<<COM20) ) ; // SET COM21=1 & COM20=1
				// END OF TIMER2 SET
			}
			break;

			case TIMER1:/*********** TIMER1 SET *********/
			{
				TCCR1A |= (1<<COM1A1) | (1<<COM1A0);
				// END OF TIMER1 SET
			}
			break;

			default:   TIMER.IS_init = NOT_INITIALIZED;
			break;

			// END OF SWITCH TIMER ID
			}

		}
		// END OF SET
		break;


		default:   TIMER.IS_init = NOT_INITIALIZED;
		break;

		/******************** END OF SWITCH COM mode    ********************/
		}


		/////****************************************************************************************************************////


		// END OF IF IS_init
	}



	/*********** END OF TIMER_init  ***********/
}

/////****************************************************************************************************************////
/////****************************************************************************************************************////
/////****************************************************************************************************************////


void TIMER_interrupt(void){

	if( TIMER.IS_init == INITIALIZED )
	{

		switch(TIMER.interrupt)
		{   /********************  INTERRUPT  ********************/

		case INTERRUPT: 		sei();
		{  /***********   INTERRUPT  *********/

			switch(TIMER.TIMER_ID)
			{

			case TIMER0:/*********** TIMER0 INTERRUPT *********/
			{
				switch(TIMER.WGM_Mode)
				{   //WGM mode
				case NORMAL_MODE: TIMSK |= (1u<<TOIE0); //Overflow Interrupt Enable
				break;
				case CTC_MODE: 	TIMSK |= (1u<<OCIE0); // Output Compare Match Interrupt Enable
				break;
				default:   TIMER.IS_init = NOT_INITIALIZED;
				break;
				}
				// END OF TIMER0 INTERRUPT
			}
			break;

			case TIMER2:/*********** TIMER2 INTERRUPT *********/
			{
				switch(TIMER.WGM_Mode)
				{   //WGM mode
				case NORMAL_MODE: TIMSK |= (1u<<TOIE2); //Overflow Interrupt Enable
				break;
				case CTC_MODE:	  TIMSK |= (1u<<OCIE2); // Output Compare Match Interrupt Enable
				break;
				default:   TIMER.IS_init = NOT_INITIALIZED;
				break;
				}

				// END OF TIMER2 INTERRUPT
			}
			break;

			case TIMER1:/*********** TIMER1 INTERRUPT *********/
			{
				switch(TIMER.WGM_Mode)
				{   //WGM mode
				case NORMAL_MODE: TIMSK|= (1<<TOIE1);     //Overflow Interrupt Enable
				break;
				case CTC_MODE:  TIMSK |= (1<<OCIE1A); 	//Output Compare Interrupt Enable  1A.
				//TIMSK|= (1<<OCIE1B)					//Output Compare Interrupt Enable  1B.
				break;
				default:   TIMER.IS_init = NOT_INITIALIZED;
				break;
				}
				// END OF TIMER1 INTERRUPT
			}
			break;

			default:   TIMER.IS_init = NOT_INITIALIZED;
			break;

			// END OF SWITCH TIMER ID
			}
		}
		// END OF INTERRUPT
		break;

		case POOLING:
		{  /***********   POOLING *********/
			switch(TIMER.TIMER_ID)
			{

			case TIMER0:/*********** TIMER0 POOLING *********/
			{
				TIMSK &= (~ ( (1u<<OCIE0) |(1u<<TOIE0) ) );  //Overflow Interrupt & Output Compare Match Interrupt disabled
				// END OF TIMER0 POOLING
			}
			break;

			case TIMER2:/*********** TIMER2 POOLING *********/
			{
				TIMSK &= (~ ( (1u<<OCIE2) |(1u<<TOIE2) ) );  //Overflow Interrupt & Output Compare Match Interrupt disabled
				// END OF TIMER2 POOLING
			}
			break;

			case TIMER1:/*********** TIMER1 POOLING *********/
			{
				TIMSK &= (~  ( (1<<TOIE1) | (1<<OCIE1A) | (1<<OCIE1B) ) ); // Output Compare A Match Interrupt Enable & Output Compare B Match Interrupt Enable & Overflow Interrupt Enable disabled

				// END OF TIMER1 POOLING
			}
			break;


			default:   TIMER.IS_init = NOT_INITIALIZED;
			break;
			// END OF SWITCH TIMER ID
			}
		}
		// END OF POOLING
		break;


		default:   TIMER.IS_init = NOT_INITIALIZED;
		break;

		/******************** END OF SWITCH INTERRUPT    ********************/
		}

		// END OF IF TIMER IS INITIALIZED
	}
	/*********** END OF TIMER_INTERRUPT  ***********/
}




/////****************************************************************************************************************////
/////****************************************************************************************************************////
/////****************************************************************************************************************////

void TIMER_start(void)
{

	TIMER_interrupt(); // SET The interrupt

	switch(TIMER.TIMER_ID)
	{

	case TIMER0:   /*********** TIMER0  *********/
	{
		switch(TIMER.prescaler)
		{
		case PPULLCALER0: TCCR0 |= 0b00000001;
		break;
		case PPULLCALER8: TCCR0 |= 0b00000010;
		break;
		case PPULLCALER64: TCCR0  |= 0b00000011;
		break;
		case PPULLCALER256: TCCR0  |= 0b00000100;
		break;
		case PPULLCALER1024: TCCR0  |= 0b00000101;
		break;
		case EXTERNAL_CLK_FALLING : TCCR0  |= 0b00000110;
		break;
		case EXTERNAL_CLK_RISING: TCCR0 |= 0b00000111;
		break;
		default: TIMER.IS_init = NOT_INITIALIZED;
		break;
		}
		//  END OF TIMER0
	}
	break;

	case TIMER2: /*********** TIMER2  *********/
	{
		switch(TIMER.prescaler)
		{
		case PPULLCALER0: TCCR2 |= 0b00000001;
		break;
		case PPULLCALER8: TCCR2 |= 0b00000010;
		break;
		case PPULLCALER32: TCCR2  |= 0b00000011;
		break;
		case PPULLCALER64: TCCR2  |= 0b00000100;
		break;
		case PPULLCALER128: TCCR2  |= 0b00000101;
		break;
		case PPULLCALER256: TCCR2  |= 0b00000110;
		break;
		case PPULLCALER1024: TCCR2 |= 0b00000111;
		break;
		default: TIMER.IS_init = NOT_INITIALIZED;
		break;
		}
		// END OF TIMER2
	}
	break;

	case TIMER1:/*********** TIMER1  *********/
	{
		switch(TIMER.prescaler)
		{
		case PPULLCALER0: TCCR1B |= 0b00000001;
		break;
		case PPULLCALER8: TCCR1B |= 0b00000010;
		break;
		case PPULLCALER64: TCCR1B |= 0b00000011;
		break;
		case PPULLCALER256: TCCR1B |= 0b00000100;
		break;
		case PPULLCALER1024: TCCR1B |= 0b00000101;
		break;
		case EXTERNAL_CLK_FALLING : TCCR1B |= 0b00000110;
		break;
		case EXTERNAL_CLK_RISING: TCCR1B |= 0b00000111;
		break;
		default: TIMER.IS_init = NOT_INITIALIZED;
		break;
		}

		break;
		// END OF TIMER1
	}
	break;

	default:   TIMER.IS_init = NOT_INITIALIZED;
	break;

	// END OF SWITCH TIMER ID
	}


	/*********** END OF TIMER_start  ***********/
}



/////****************************************************************************************************************////
/////****************************************************************************************************************////
/////****************************************************************************************************************////



void TIMER_stop(void)
{


	switch(TIMER.TIMER_ID)
	{

	case TIMER0:   /*********** TIMER0  *********/
	{
		TCCR0 &= 0b11111000;
		//  END OF TIMER0
	}
	break;

	case TIMER2: /*********** TIMER2  *********/
	{
		TCCR2 &= 0b11111000;
		// END OF TIMER2
	}
	break;

	case TIMER1:/*********** TIMER1  *********/
	{
		TCCR1B &= 0b11111000;
		// END OF TIMER1
	}
	break;



	default:   TIMER.IS_init = NOT_INITIALIZED;
	break;

	// END OF SWITCH TIMER ID
	}


	/*********** END OF TIMER_stop  ***********/
}




/////****************************************************************************************************************////
/////****************************************************************************************************************////
/////****************************************************************************************************************////


//*********** INTERRUPT TIMERS HANDELER *********//

/*********** TIMER0  *********/

ISR(TIMER0_OVF_vect)
{
	num+=1;
	if(num==4000){
		TIME_flag=1;
		num=0;
	}
}

ISR(TIMER0_COMP_vect)
{

}

/*********** TIMER1  *********/

ISR(TIMER1_OVF_vect)
{

}

ISR(TIMER1_COMPA_vect)
{

}

/*********** TIMER2  *********/

ISR(TIMER2_OVF_vect)
{


}

ISR(TIMER2_COMP_vect)
{


}








