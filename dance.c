#include "dance.h"
#include <pololu/orangutan.h>
/*
 * buzzer1: for the Orangutan LV/SV-xx8
 *
 * Uses the OrangutanBuzzer library to play a series of notes on the
 * Orangutan's buzzer.  It also uses the OrangutanLCD library to
 * display the notes its playing, and it uses the OrangutanPushbuttons
 * library to allow the user to stop/reset the melody with the top
 * pushbutton.
 *
 * http://www.pololu.com/docs/0J20/6.d
 * http://www.pololu.com
 * http://forum.pololu.com
 */

#define MELODY_LENGTH 203
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988

// These arrays take up a total of 285 bytes of RAM (out of a 1k limit)
unsigned int note[MELODY_LENGTH] =
        {
                NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
                NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
                NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
                NOTE_A4, NOTE_G4, NOTE_A4, 0,

                NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
                NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
                NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
                NOTE_A4, NOTE_G4, NOTE_A4, 0,

                NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
                NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
                NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
                NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

                NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
                NOTE_D5, NOTE_E5, NOTE_A4, 0,
                NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
                NOTE_C5, NOTE_A4, NOTE_B4, 0,

                NOTE_A4, NOTE_A4,
                //Repeat of first part
                NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
                NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
                NOTE_A4, NOTE_G4, NOTE_A4, 0,

                NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
                NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
                NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
                NOTE_A4, NOTE_G4, NOTE_A4, 0,

                NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
                NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
                NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
                NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

                NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
                NOTE_D5, NOTE_E5, NOTE_A4, 0,
                NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
                NOTE_C5, NOTE_A4, NOTE_B4, 0,
                //End of Repeat

                NOTE_E5, 0, 0, NOTE_F5, 0, 0,
                NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
                NOTE_D5, 0, 0, NOTE_C5, 0, 0,
                NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

                NOTE_E5, 0, 0, NOTE_F5, 0, 0,
                NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
                NOTE_D5, 0, 0, NOTE_C5, 0, 0,
                NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
        };

unsigned int duration[MELODY_LENGTH] =
        {
                125, 125, 250, 125, 125,
                125, 125, 250, 125, 125,
                125, 125, 250, 125, 125,
                125, 125, 375, 125,

                125, 125, 250, 125, 125,
                125, 125, 250, 125, 125,
                125, 125, 250, 125, 125,
                125, 125, 375, 125,

                125, 125, 250, 125, 125,
                125, 125, 250, 125, 125,
                125, 125, 250, 125, 125,
                125, 125, 125, 250, 125,

                125, 125, 250, 125, 125,
                250, 125, 250, 125,
                125, 125, 250, 125, 125,
                125, 125, 375, 375,

                250, 125,
                //Rpeat of First Part
                125, 125, 250, 125, 125,
                125, 125, 250, 125, 125,
                125, 125, 375, 125,

                125, 125, 250, 125, 125,
                125, 125, 250, 125, 125,
                125, 125, 250, 125, 125,
                125, 125, 375, 125,

                125, 125, 250, 125, 125,
                125, 125, 250, 125, 125,
                125, 125, 250, 125, 125,
                125, 125, 125, 250, 125,

                125, 125, 250, 125, 125,
                250, 125, 250, 125,
                125, 125, 250, 125, 125,
                125, 125, 375, 375,
                //End of Repeat

                250, 125, 375, 250, 125, 375,
                125, 125, 125, 125, 125, 125, 125, 125, 375,
                250, 125, 375, 250, 125, 375,
                125, 125, 125, 125, 125, 500,

                250, 125, 375, 250, 125, 375,
                125, 125, 125, 125, 125, 125, 125, 125, 375,
                250, 125, 375, 250, 125, 375,
                125, 125, 125, 125, 125, 500
        };

unsigned int current_choreography_step;
unsigned long last_time_into;

struct choreography_step {
public:
  int right_engine;
  int left_engine;
  unsigned int duration;
  choreography_step(int right_engine,int left_engine,unsigned int duration){
    right_engine = right_engine;
    left_engine = left_engine;
    duration = duration;
  }
}

// Coreo info: moto
#define choreography_size 5
choreography_step choreography[choreography_size] = {
  choreography_step(50, 50, 1000),
  choreography_step(-50, -50, 1000),
  choreography_step(-20, -50, 1000),
  choreography_step(-50, -20, 1000)
 }
unsigned char currentIdx;
short int count;
unsigned char old_move;

void dance(short int count, unsigned char *old_move) {
    if (count >= 6000 && *old_move == 5) {
        print("Mov_6");
        set_motors(0, 0);
        set_motors(-50, -50);
        *old_move = 0;
    } else if (count >= 5000 && *old_move == 4) {
        print("Mov_5");
        set_motors(0, 0);
        set_motors(-20, -50);
        *old_move = 5;
    } else if (count >= 4000 && *old_move == 3) {
        print("Mov_4");
        set_motors(0, 0);
        set_motors(20, 50);
        *old_move = 4;
    } else if (count >= 3000 && *old_move == 2) {
        print("Mov_3");
        set_motors(0, 0);
        set_motors(-50, -20);
        *old_move = 3;
    } else if (count >= 2000 && *old_move == 1) {
        print("Mov_2");
        set_motors(0, 0);
        set_motors(50, 20);
        *old_move = 2;
    } else if (count >= 1000 && *old_move == 0) {
        print("Mov_1");
        set_motors(0, 0);
        set_motors(50, 50);
        *old_move = 1;
    }
}

/**
 * Function executed only one time to setup before any one
 */
void dance_mode_setup() {
    // Nothing to do
}

/**
 * Function executed when mode is stopped and relaunch.
 * If on_mode_create is executed, then this will be executed
 */
void dance_mode_start() {
    currentIdx = 0;
    count = 0;
    old_move = 0;
    current_choreography_step = 0;
}

/**
 * Function executed when mode is paused an resume ( When someone press the mode assigned key ).
 * If on_mode_start is executed, then this will be executed
 */
void dance_mode_resume() {
    set_motors(0, 0);
    last_time_into = 0;
}

/**
 * Function executed when mode is paused ( When someone press the mode assigned key )
 */
void dance_mode_pause() {
    set_motors(0, 0);
    if (is_playing()) stop_playing();
}

/**
 * Function executed when mode is stopped ( When someone press a different mode assigned key ). Its always be executed after
 * on_mode_pause.
 */
void dance_mode_stop() {}

/**
 * Main loop of the mode
 */
void dance_mode_loop() {
    // if we haven't finished playing the song and
    // the buzzer is ready for the next note, play the next note
    if (currentIdx < MELODY_LENGTH && !is_playing()) {
        // play note at max volume
        play_frequency(note[currentIdx], duration[currentIdx] * 2, 15);
        currentIdx++;
    }
    //If the song is finished, restart the song.
    else if (currentIdx == MELODY_LENGTH) {
        currentIdx = 0;
    }

    if (get_ms() - last_time_into > choreography[current_choreography_step].duration) {
        last_time_into = get_ms();
        current_choreography_step = (current_choreography_step + 1)%choreography_size;
        set_motors(choreography[current_choreography_step].right_engine, choreography[current_choreography_step].left_engine);
      }
}
