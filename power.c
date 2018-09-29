//
// Created by abel on 29/09/18.
//

#include "power.h"

/**
 * Function executed only first time mode is executed
 */
void power_mode_create(){}

/**
 * Function executed when mode is stopped and relaunch.
 * If on_mode_create is executed, then this will be executed
 */
void power_mode_start(){}

/**
 * Function executed when mode is paused an resume ( When someone press the mode assigned key ).
 * If on_mode_start is executed, then this will be executed
 */
void power_mode_resume(){}

/**
 * Function executed when mode is paused ( When someone press the mode assigned key )
 */
void power_mode_pause(){}

/**
 * Function executed when mode is stopped ( When someone press a different mode assigned key ). Its always be executed after
 * on_mode_pause.
 */
void power_mode_stop(){}

/**
 * Main loop of the mode
 */
void power_mode_loop(){}