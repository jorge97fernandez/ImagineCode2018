//
// Created by abel on 29/09/18.
//
#include "race_white.h"
#include <pololu/3pi.h>

static unsigned int sensors[5]; // an array to hold sensor values
static int integral = 0;
static int last_proportional = 0;
static const int max = 140;
static int power_difference, derivative, proportional;
static unsigned int position;

void race_white_mode_resume() {
    set_motors(0, 0);
}

/**
 * Main loop of the mode
 */
void race_white_mode_loop() {
    // Get the position of the line.  Note that we *must* provide
    // the "sensors" argument to read_line() here, even though we
    // are not interested in the individual sensor readings.
    position = read_line(sensors, IR_EMITTERS_ON);

    if (position >= 0 && position < 2000) proportional = position;
    else if (position > 2000 && position <= 4000) proportional = position - 4000;
    else {
        position = read_line(sensors, IR_EMITTERS_ON);
        if (position >= 0 && position < 2000) proportional = 2000;
        else proportional = -2000;
    }
    derivative = proportional - last_proportional;
    integral += proportional;
    last_proportional = proportional;
    power_difference = proportional * 1 / 8 + integral / 10000 + derivative * 25 / 10;

    if (power_difference > max) power_difference = max;
    if (power_difference < -max) power_difference = -max;
    if (power_difference < 0) set_motors(max + power_difference, max);
    else set_motors(max, max - power_difference);
}
