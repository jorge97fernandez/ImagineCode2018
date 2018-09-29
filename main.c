#include <pololu/orangutan.h>
/* 
 * This code will follow a black path between two black lines, using a
 * very simple algorithm.  It demonstrates auto-calibration and use of
 * the 3pi IR sensors, motor control, bar graphs using custom
 * characters, and music playback, making it a good starting point for
 * developing your own more competitive line follower.
 */

// This function displays the sensor readings using a bar graph.
void display_readings(const unsigned int *calibrated_values)
{
	unsigned char i;

	for(i=0;i<5;i++) {
		// Initialize the array of characters that we will use for the
		// graph.  Using the space, an extra copy of the one-bar
		// character, and character 255 (a full black box), we get 10
		// characters in the array.
		const char display_characters[10] = {' ',0,0,1,2,3,4,5,6,255};

		// The variable c will have values from 0 to 9, since
		// calibrated values are in the range of 0 to 1000, and
		// 1000/101 is 9 with integer math.
		char c = display_characters[calibrated_values[i]/101];

		// Display the bar graph character.
		print_character(c);
	}
} 

// Show values OF calibration
void show_calibration_values(){
	unsigned int counter; // used as a simple timer
	// Auto-calibration: turn right and left while calibrating the
	// sensors.
	for(counter=0;counter<80;counter++)
	{
		if(counter < 20 || counter >= 60)
			set_motors(40,-40);
		else
			set_motors(-40,40);

		// This function records a set of sensor readings and keeps
		// track of the minimum and maximum values encountered.  The
		// IR_EMITTERS_ON argument means that the IR LEDs will be
		// turned on during the reading, which is usually what you
		// want.
		calibrate_line_sensors(IR_EMITTERS_ON);

		// Since our counter runs to 80, the total delay will be
		// 80*20 = 1600 ms.
		delay_ms(20);
	}
	set_motors(0,0);

		// Display maximum
	unsigned int* maximum = get_line_sensors_calibrated_maximum_on();
	for(int i = 0 ; i< 5; i++){
	while(!button_is_pressed(BUTTON_B))
	{
		clear();
		print_long(maximum[i]);
		lcd_goto_xy(0,1);
		delay_ms(100);
	}
	wait_for_button_release(BUTTON_B);
	}


			// Display maximum
	unsigned int* minimum = get_line_sensors_calibrated_minimum_on();
		for(int i = 0 ; i< 5; i++){
		while(!button_is_pressed(BUTTON_B))
	{
		clear();
		print_long(minimum[i]);
		lcd_goto_xy(0,1);
		delay_ms(100);
	}
		wait_for_button_release(BUTTON_B);
	}

	clear();
	print("Finish!");
	while(1){}
	
}
	unsigned int sensors[5]; // an array to hold sensor values

	// This must be called at the beginning of 3pi code, to set up the
	// sensors.  We use a value of 2000 for the timeout, which
	// corresponds to 2000*0.4 us = 0.8 ms on our 20 MHz processor.
	pololu_3pi_init(2000);
	load_custom_characters(); // load the custom characters
	
	// Play welcome music and display a message
	print_from_program_space(welcome_line1);
	lcd_goto_xy(0,1);
	print_from_program_space(welcome_line2);
	play_from_program_space(welcome);
	delay_ms(1000);

	clear();
	print_from_program_space(demo_name_line1);
	lcd_goto_xy(0,1);
	print_from_program_space(demo_name_line2);
	delay_ms(1000);

	// Display battery voltage and wait for button press
	while(!button_is_pressed(BUTTON_B))
	{
		int bat = read_battery_millivolts();

		clear();
		print_long(bat);
		print("mV");
		lcd_goto_xy(0,1);
		print("Press B");

		delay_ms(100);
	}

	// Always wait for the button to be released so that 3pi doesn't
	// start moving until your hand is away from it.
	wait_for_button_release(BUTTON_B);

	#define AUTO_CALIBRATE 0
	#if AUTO_CALIBRATE
		// Only first time
		show_calibration_values();
	#else
	    calibrate_line_sensors(IR_EMITTERS_ON);
		unsigned int* maximum = get_line_sensors_calibrated_maximum_on();
		maximum[0]=2000;
		maximum[1]=1896;
		maximum[2]=1801;
		maximum[3]=2000;
		maximum[4]=2000;
	
		unsigned int* minimum = get_line_sensors_calibrated_minimum_on();
		minimum[0]=421;
		minimum[1]=310;
		minimum[2]=268;
		minimum[3]=330;
		minimum[4]=467;

	#endif

	clear();

	print("Go!");	

	delay_ms(1000);	

	clear();
}

int main()                    // run once, when the sketch starts
{
	unsigned int sensors[5]; // an array to hold sensor values

	// set up the 3pi
	initialize();

	// This is the "main loop" - it will run forever.
	while(1)
	{
		// Get the position of the line.  Note that we *must* provide
		// the "sensors" argument to read_line() here, even though we
		// are not interested in the individual sensor readings.
		unsigned int position = read_line(sensors,IR_EMITTERS_ON);

		if(position == 0 || position == 4000)
		{
			// We are far to the right of the line: turn left.

			// Set the right motor to 100 and the left motor to zero,
			// to do a sharp turn to the left.  Note that the maximum
			// value of either motor speed is 255, so we are driving
			// it at just about 40% of the max.
			set_motors(40,40);
		}
		else if(position < 2000)
		{
			// We are somewhat close to being centered on the line:
			// drive straight.
			set_motors(50,0);
		}
		else
		{
			// We are far to the left of the line: turn right.
			set_motors(0,50);
		}
  }
}
