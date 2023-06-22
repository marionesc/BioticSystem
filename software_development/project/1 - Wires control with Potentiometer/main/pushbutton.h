/* This library has been designed to control a 4-digit 7-segment display. It has been verified with a Luckylight display.
 * DISPLAY REFERENCE :  Luckylight L1309088
 * NUMBER OF PIN :      14 pins
 * COMPOSITION :        3 push-button with 4 pins, 3 resistor of 1kohms
 *
 * Created by Marion escouteloup, @maesc on Github
 * Creation date  : 22-06-2023 (DD/MM/YYYY)
 * Last update    : 22-06-2023 (DD-MM-YYYY)
 */

#ifndef pushbutton_h
#define pushbutton_h

#include "Arduino.h"
#include <Wire.h>	

class pushbutton{
  public : 

    pushbutton(int pinpb1, int pinpb2, int pinpb3, int rebounds); 
    void  init_pushButtons();
    int   set_wireselect(int wiresel); 
    int   set_wireactive(int wireact, int wiresel); 
    bool  saveButtonActive(); 
    
  private : 
    int _BP1_IN; 
    int _BP2_IN; 
    int _BP3_IN; 

    bool _bp1_oi; // Status of push button during previous playback (_oi : older input)
    bool _bp2_oi;
    bool _bp3_oi;         

    int _BP_BOUNCE; 

};
#endif