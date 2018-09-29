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

#define MELODY_LENGTH 37
#define c = 261;
#define d = 294;
#define e = 329;
#define f = 349;
#define g = 391;
#define gS = 415;
#define a = 440;
#define aS = 455;
#define b = 466;
#define cH = 523;
#define cSH = 554;
#define dH = 587;
#define dSH = 622;
#define eH = 659;
#define fH = 698;
#define fSH = 740;
#define gH = 784;
#define gSH = 830;
#define aH = 880;

// These arrays take up a total of 285 bytes of RAM (out of a 1k limit)
unsigned char note[MELODY_LENGTH] = 
{
  a,a,a,f,cH,a,f,cH,a,SILENT_NOTE,eH,eH,eH,fH,cH,gS,f,cH,a,SILENT_NOTE,aH,a,a,aH,gSH,gH,fSH,fH,fSH,SILENT_NOTE,aS,dSH,dH,cSH,cH,bcH,SILENT_NOTE
};

unsigned int duration[MELODY_LENGTH] =
{
500,500,500,350,150,500,350,150,650,500,500,500,500,350,150,500,350,150,650,500,500,300,150,500,325,175,125,125,250,325,250,500,325,175,125,  
125,250,350,
};

unsigned char currentIdx;

int main()                    // run once, when the sketch starts
{
  currentIdx = 0;
  print("Music!");

  while(1)                     // run over and over again
  {
    // if we haven't finished playing the song and 
    // the buzzer is ready for the next note, play the next note
    if (currentIdx < MELODY_LENGTH && !is_playing())
    {
      // play note at max volume
      play_note(note[currentIdx], duration[currentIdx], 15);
      
      // optional LCD feedback (for fun)
      lcd_goto_xy(0, 1);                           // go to start of the second LCD line
	  if(note[currentIdx] != 255) // display blank for rests
        print_long(note[currentIdx]);  // print integer value of the current note
      print("  ");                            // overwrite any left over characters
      currentIdx++;
    }

    // Insert some other useful code here...
    // the melody will play normally while the rest of your code executes
    // as long as it executes quickly enough to keep from inserting delays
    // between the notes.
  
    // For example, let the top user pushbutton function as a stop/reset melody button
    if (button_is_pressed(TOP_BUTTON))
    {
      stop_playing(); // silence the buzzer
      if (currentIdx < MELODY_LENGTH)
        currentIdx = MELODY_LENGTH;        // terminate the melody
      else
        currentIdx = 0;                    // restart the melody
      wait_for_button_release(TOP_BUTTON);  // wait here for the button to be released
    }
  }
}
