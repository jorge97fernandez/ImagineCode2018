//
// Created by abel on 29/09/18.
//

#include "power.h"

unsigned long last_time_into;

/**
 * Function executed only first time mode is executed
 */
void power_mode_setup(){
    // Nothing to do
}

/**
 * Function executed when mode is stopped and relaunch.
 * If on_mode_create is executed, then this will be executed
 */
void power_mode_start(){
    // Nothing to do
}

/**
 * Function executed when mode is paused an resume ( When someone press the mode assigned key ).
 * If on_mode_start is executed, then this will be executed
 */
void power_mode_resume(){
    last_time_into = get_ms();
    clear();
    print_long(0);
}

/**
 * Function executed when mode is paused ( When someone press the mode assigned key )
 */
void power_mode_pause(){
    // Nothing to do
}

/**
 * Function executed when mode is stopped ( When someone press a different mode assigned key ). Its always be executed after
 * on_mode_pause.
 */
void power_mode_stop(){
    // Nothing to do
}

/**
 * Main loop of the mode
 */
void power_mode_loop(){
    unsigned long diff = (last_time_into - get_ms());
    if(diff > 200){
        last_time_into = get_ms();
        //int bat = read_battery_millivolts();
        clear();
        print_long(555);
        //print("mV");
    }
}