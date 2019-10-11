#include "lcd.h"
#include "uart.h"
#include "common_macros.h"
#include <util/delay.h>

int main(void)
{
	SET_BIT(DDRC,4);
	UART_init();
	LCD_init();
	uint8 num = '0';
    while(1)
    {
		if( BIT_IS_SET(PINC, 4))
		{
			if(num >= '0' && num <= '9')
			{
				_delay_ms(100); // debounce
				UART_sendByte(num);
				LCD_clearScreen();
				LCD_displayCharacter((uint8) num);
				_delay_ms(500);
				num++;
			}
			else
			{
				num = '0';
				UART_sendByte(num);
				LCD_clearScreen();
				LCD_displayCharacter((uint8) num);
 				_delay_ms(500);
				num++;
			}
		}
		
    }
}
