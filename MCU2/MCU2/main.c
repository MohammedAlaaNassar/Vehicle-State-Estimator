
#include "uart.h"
#include "lcd.h"

int main(void)
{
	uint8 key;
	UART_init();
	LCD_init();
    while(1)
    {
		key = UART_recieveByte(); //receive the pressed key from uart
		if( (key >= '0') && (key <= '9') )
		{
			LCD_clearScreen();
			LCD_displayCharacter((uint8) key); //display the pressed keypad switch	
		}
		else
		{
			LCD_clearScreen();
			LCD_displayCharacter('0'); //display the pressed keypad switch
		}		 
    }
}
