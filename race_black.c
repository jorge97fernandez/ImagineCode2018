//
// Created by abel on 29/09/18.
//

#include "race_black.h"
#include <pololu/3pi.h>

static unsigned int sensors[5]; // an array to hold sensor values
static int integral = 0;
static int last_proportional = 0;
static const int max = 255;
static int power_difference, derivative, proportional;
static unsigned int position;

/**
 * Function executed when mode is paused an resume ( When someone press the mode assigned key ).
 * If on_mode_start is executed, then this will be executed
 */
void race_black_mode_resume() {
    set_motors(0, 0);
}

/**
 * Main loop of the mode
 */
void race_black_mode_loop() {
    position = read_line(sensors, IR_EMITTERS_ON);
    proportional = ((int) position) - 2000;
    derivative = proportional - last_proportional;
    integral += proportional;
    last_proportional = proportional;
    power_difference = proportional / 20 + integral / 10000 + derivative * 5 / 2;
    if (power_difference > max) power_difference = max;
    if (power_difference < -max) power_difference = -max;
    if (power_difference < 0) set_motors(max + power_difference, max);
    else set_motors(max, max - power_difference);
}
