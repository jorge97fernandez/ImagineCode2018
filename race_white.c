//
// Created by abel on 29/09/18.
//

#include "race_white.h"

/**
 * Function executed only first time mode is executed
 */
void race_white_mode_setup(){}

/**
 * Function executed when mode is stopped and relaunch.
 * If on_mode_create is executed, then this will be executed
 */
void race_white_mode_start(){}

/**
 * Function executed when mode is paused an resume ( When someone press the mode assigned key ).
 * If on_mode_start is executed, then this will be executed
 */
void race_white_mode_resume(){}

/**
 * Function executed when mode is paused ( When someone press the mode assigned key )
 */
void race_white_mode_pause(){}

/**
 * Function executed when mode is stopped ( When someone press a different mode assigned key ). Its always be executed after
 * on_mode_pause.
 */
void race_white_mode_stop(){}

/**
 * Main loop of the mode
 */
void race_white_mode_loop(){

}
