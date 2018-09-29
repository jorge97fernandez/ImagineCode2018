//
// Created by abel on 29/09/18.
//

#include "race.h"

/**
 * Function executed only first time mode is executed
 */
void race_mode_setup(){
}

/**
 * Function executed when mode is stopped and relaunch.
 * If on_mode_create is executed, then this will be executed
 */
void race_mode_start(){
  set_motors(0, 0);
}

/**
 * Function executed when mode is paused an resume ( When someone press the mode assigned key ).
 * If on_mode_start is executed, then this will be executed
 */
void race_mode_resume(){
  race_white_mode_resume();
}

/**
 * Function executed when mode is paused ( When someone press the mode assigned key )
 */
void race_mode_pause(){
  set_motors(0, 0);
}

/**
 * Function executed when mode is stopped ( When someone press a different mode assigned key ). Its always be executed after
 * on_mode_pause.
 */
void race_mode_stop(){
  set_motors(0, 0);
}

/**
 * Main loop of the mode
 */
void race_mode_loop(){
  race_white_mode_loop();
}
