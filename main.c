/* ImagineCode - an application for the Pololu 3pi Robot
 *
 * This application uses the Pololu AVR C/C++ Library.  For help, see:
 * -User's guide: http://www.pololu.com/docs/0J20
 * -Command reference: http://www.pololu.com/docs/0J18
 *
 * Created: 9/29/2018 12:00:28 AM
 *  Author: Daniel
 */

#include <pololu/3pi.h>

int main()
{
	//play_from_program_space(PSTR(">g32>>c32"));  // Play welcoming notes.

	/*while(1)
	{
		// Print battery voltage (in mV) on the LCD.
		clear();
		print_long(read_battery_millivolts_3pi());

		red_led(1);     // Turn on the red LED.
		delay_ms(200);  // Wait for 200 ms.

		red_led(0);     // Turn off the red LED.
		delay_ms(200);  // Wait for 200 ms.
	}*/
	while(1)
	{
		print("JORGE"); // display "Hello" at (0, 0), a.k.a. upper-left
		delay_ms(200);
		lcd_scroll(LCD_RIGHT, 3, 200);// shift the display right every 200ms three times
		clear(); // clear the LCD
		lcd_goto_xy(3, 1); // go to the fourth character of the second LCD line
		print("JORGE"); // display "Hello" at (3, 1), a.k.a. lower-right
		delay_ms(200);
		lcd_scroll(LCD_LEFT, 3, 200); // shift the display left every 200ms three times
		clear(); // clear the LCD
	}
	/*for (int i = 0; i < 5; ++i)
	{
		set_motors(10, 10);
		//red_led(0);
		//green_led(1);
		delay_ms(1000);
		set_motors(-10,-10);
		//green_led(0);
		//red_led(1);
		set_motors(0,0);
		delay_ms(500);
		set_motors(0,10);
		delay_ms(1000);
		set_motors(0,0);
		delay_ms(500);
		set_motors(10,0);
		delay_ms(1000);
		set_motors(0,0);
		delay_ms(500);
	}*/
	//set_motors(0,0);
	return 0;
}
