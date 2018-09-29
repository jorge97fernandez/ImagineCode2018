/*
 * This code will follow a black path between two black lines, using a
 * very simple algorithm.  It demonstrates auto-calibration and use of
 * the 3pi IR sensors, motor control, bar graphs using custom
 * characters, and music playback, making it a good starting point for
 * developing your own more competitive line follower.
 */

// The 3pi include file must be at the beginning of any program that
// uses the Pololu AVR library and 3pi.
#include <pololu/3pi.h>

// This include file allows data to be stored in program space.  The
// ATmega168 has 16k of program space compared to 1k of RAM, so large
// pieces of static data should be stored in program space.
#include <avr/pgmspace.h>

// Introductory messages.  The "PROGMEM" identifier causes the data to
// go into program space.
const char msg_panteras[]
PROGMEM = "Panteras";
const char msg_manila[]
PROGMEM = "Manila";
const char msg_select[]
PROGMEM = "select";
const char msg_mode[]
PROGMEM = "mode";
const char msg_race[]
PROGMEM = "race";
const char msg_dance[]
PROGMEM = "dance";
const char msg_power[]
PROGMEM = "power";
const char msg_paused[]
PROGMEM = "paused";
const char msg_go[]
PROGMEM = "Go!";
const char msg_dancing[]
PROGMEM = "Dancing";

// BUTTONS FOR MODES
#define MODE_RACE_BUTTON BUTTON_A
#define MODE_DANCE_BUTTON BUTTON_B
#define MODE_POWER_BUTTON BUTTON_C

// A couple of simple tunes, stored in program space.
const char welcome[]
PROGMEM = ">g32>>c32";
const char go[]
PROGMEM = "L16 cdegreg4";

// Data for generating the characters used in load_custom_characters
// and display_readings.  By reading levels[] starting at various
// offsets, we can generate all of the 7 extra characters needed for a
// bargraph.  This is also stored in program space.
const char levels[]
PROGMEM = {
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111
};

// This function loads custom characters into the LCD.  Up to 8
// characters can be loaded; we use them for 7 levels of a bar graph.
void load_custom_characters() {
    lcd_load_custom_character(levels + 0, 0); // no offset, e.g. one bar
    lcd_load_custom_character(levels + 1, 1); // two bars
    lcd_load_custom_character(levels + 2, 2); // etc...
    lcd_load_custom_character(levels + 3, 3);
    lcd_load_custom_character(levels + 4, 4);
    lcd_load_custom_character(levels + 5, 5);
    lcd_load_custom_character(levels + 6, 6);
    clear(); // the LCD must be cleared for the characters to take effect
}

// Initializes the 3pi, displays a welcome message, calibrates, and
// plays the initial music.
void initialize() {
    // This must be called at the beginning of 3pi code, to set up the
    // sensors.  We use a value of 2000 for the timeout, which
    // corresponds to 2000*0.4 us = 0.8 ms on our 20 MHz processor.
    pololu_3pi_init(2000);
    load_custom_characters(); // load the custom characters

    calibrate_line_sensors(IR_EMITTERS_ON);
    unsigned int *maximum = get_line_sensors_calibrated_maximum_on();
    maximum[0] = 2000;
    maximum[1] = 1896;
    maximum[2] = 1801;
    maximum[3] = 2000;
    maximum[4] = 2000;

    unsigned int *minimum = get_line_sensors_calibrated_minimum_on();
    minimum[0] = 421;
    minimum[1] = 310;
    minimum[2] = 268;
    minimum[3] = 330;
    minimum[4] = 467;
}

/**
 * Muestra un mensaje de dos lineas en la pantalla
 */
void display_message(char* line1, char* line2){
    clear();
    lcd_goto_xy(0, 0);
    print_from_program_space(line1);
    lcd_goto_xy(0, 1);
    print_from_program_space(line2);
}

/**
 * Muestra un mensaje de dos lineas en la pantalla
 */
void display_message_centred(char* line1){
    clear();
    print_from_program_space(line1);
}

// This is the main function, where the code starts.  All C programs
// must have a main() function defined somewhere.
int main() {
    // set up the 3pi
    initialize();

    // muestra mensaje "Panteras Manila"
    display_message(msg_panteras, msg_manila);
    delay_ms(1000);

    //
    display_message(msg_select, msg_mode);
    unsigned char button_pressed = wait_for_button(BUTTON_A | BUTTON_B | BUTTON_C);

    // Modulo de juego seleccionado
    unsigned char selected_game_mode;

    while (1){
        // Seteamos el modo de juego
        selected_game_mode = button_pressed;

        switch(selected_game_mode){
            case MODE_RACE_BUTTON:
                display_message(msg_race, msg_mode);
                break;
            case MODE_DANCE_BUTTON:
                display_message(msg_dance, msg_mode);
                break;
            case MODE_POWER_BUTTON:
                display_message(msg_power, msg_mode);
                break;
        }

        button_pressed = wait_for_button(BUTTON_A | BUTTON_B | BUTTON_C);

        if(button_pressed != selected_game_mode){
            break; // Cambiamos de modo de juego
        }

        // TODO: Aqui se pondria el onstart y on resume en un switch aparte

GAME_MODE_LOOP_START:
        switch(selected_game_mode){
            case MODE_RACE_BUTTON:
                display_message_centred(msg_go);
                break;
            case MODE_DANCE_BUTTON:
                display_message_centred(msg_dancing);
                break;
            case MODE_POWER_BUTTON:
                display_message_centred(msg_power);
                break;
        }

        // TODO: Aqui se pondria el main loop
        while(!(button_pressed = button_is_pressed(BUTTON_A | BUTTON_B | BUTTON_C))){

        }
        wait_for_button_release(BUTTON_A | BUTTON_B | BUTTON_C);

        if(button_pressed == selected_game_mode){
            // TODO: switch haciendo el pause del modo adecuado
        }else { 
            // TODO: switch con el stop del modo adecuado
            break;
       }

        button_pressed = wait_for_button(BUTTON_A | BUTTON_B | BUTTON_C);

        if(button_pressed != selected_game_mode){
             // TODO: switch con el stop del modo adecuado
            break; // Cambiamos de modo de juego
        }
        else{
            // TODO: se hace onresume del modo adecuado
            goto GAME_MODE_LOOP_START;
        }
    }

}
