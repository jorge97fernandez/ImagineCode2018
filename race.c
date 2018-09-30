//
// Created by abel on 29/09/18.
//

#include "race.h"
#include "race_white.h"
#include "race_black.h"
#include <pololu/3pi.h>

static char race_mode_selected = 0;

/**
 * Function executed only first time mode is executed
 */
void race_mode_setup() {
}

/**
 * Function executed when mode is stopped and relaunch.
 * If on_mode_create is executed, then this will be executed
 */
void race_mode_start() {
    set_motors(0, 0);
    unsigned int sensors[5];
    unsigned int position = read_line(sensors, IR_EMITTERS_ON);
    if (position == 0 || position == 4000) {
        race_mode_selected = 1;
    } else {
        race_mode_selected = 0;
    }
}

/**
 * Function executed when mode is paused an resume ( When someone press the mode assigned key ).
 * If on_mode_start is executed, then this will be executed
 */
void race_mode_resume() {
    if (race_mode_selected) {
        race_white_mode_resume();
    } else {
        race_black_mode_resume();
    }
}

/**
 * Function executed when mode is paused ( When someone press the mode assigned key )
 */
void race_mode_pause() {
    set_motors(0, 0);
}

/**
 * Function executed when mode is stopped ( When someone press a different mode assigned key ). Its always be executed after
 * on_mode_pause.
 */
void race_mode_stop() {
    set_motors(0, 0);
}

/**
 * Main loop of the mode
 */
void race_mode_loop() {
    if (race_mode_selected) {
        race_white_mode_loop();
    } else {
        race_black_mode_loop();
    }

}
