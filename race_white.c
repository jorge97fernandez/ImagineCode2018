//
// Created by abel on 29/09/18.
//
#include "race_white.h"
#include <pololu/3pi.h>

static unsigned int sensors[5]; // an array to hold sensor values
static int integral = 0;
static int last_proportional = 0;
static int power_difference, derivative, proportional;
static unsigned int position;

void race_white_mode_resume(){
  set_motors(0, 0);
}

#define WEIGHT_ACTUAL 1250
#define WEIGHT_INTEGRAL 1
#define WEIGHT_DERIVATE 1000
#define GLOBAL_DIVISOR 10000
#define MAX_SPEED 140

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
    power_difference = (int)(((long) proportional * WEIGHT_ACTUAL  + (long) integral * WEIGHT_INTEGRAL + (long) derivative * WEIGHT_DERIVATE) / 10000);

    if (power_difference > MAX_SPEED) power_difference = MAX_SPEED;
    if (power_difference < -MAX_SPEED) power_difference = -MAX_SPEED;
    if (power_difference < 0) set_motors(MAX_SPEED + power_difference, MAX_SPEED);
    else set_motors(MAX_SPEED, MAX_SPEED - power_difference);
}
