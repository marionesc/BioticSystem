/* This library has been designed to control a 4-digit 7-segment display. It has been verified with a Luckylight display.
 * DISPLAY REFERENCE :  Luckylight L1309088
 * NUMBER OF PIN :      14 pins
 * COMPOSITION :        3 push-button with 4 pins, 3 resistor of 1kohms
 *
 * Created by Marion escouteloup, @maesc on Github
 * Creation date  : 22-06-2023 (DD/MM/YYYY)
 * Last update    : 22-06-2023 (DD-MM-YYYY)
 */

#include "Arduino.h"
#include <Wire.h>	
#include "pushbutton.h"
 
pushbutton::pushbutton(int PB1_IN, int PB2_IN, int PB3_IN, int rebounds){
  _BP1_IN = PB1_IN; 
  _BP2_IN = PB2_IN; 
  _BP3_IN = PB3_IN; 
  _BP_BOUNCE = rebounds;  
}

/** Function to initiate pin initalization for all three pushbuttons
 *    
 */
void pushbutton::init_pushButtons(){
  pinMode(_BP1_IN, INPUT);
  pinMode(_BP2_IN, INPUT);
  pinMode(_BP3_IN, INPUT);

  _bp1_oi    = digitalRead(_BP1_IN); 
  _bp2_oi    = digitalRead(_BP2_IN); 
  _bp3_oi    = digitalRead(_BP3_IN); 

  Serial.println("Push-buttons are initialized"); 
}

/** Increases the number of the selected wire each time the n°1 push-button is pressed.
 *      @param  wiresel -- The number of the currently selected wire
 *      @return output  -- The new wire selected
 */ 
int pushbutton::set_wireselect(int wiresel){
  int output = wiresel; 
  bool _bp1_ni = digitalRead (_BP1_IN);
  // If a change in push-button status is detected 
  if(_bp1_oi != _bp1_ni) {        

    // If the nw value of push-button is 1 (= PRESSED)
    if(_bp1_ni == true){        
      delay(_BP_BOUNCE);                     //  We wait for the configuree time to secure the rebound values.
    }

    // If the nw value of push-button is 0 (= RELEASED)
    else if(_bp1_ni == false){
      output++;  
      if(output > 3)
        output = 1; 
    }   
                   
    _bp1_oi = _bp1_ni;                          //  Set bp1_oi to the current value for the next loop
  }
  return output; 
} 


/** Activates the selected wire if a press on pushbutton n°2 is detected. 
 *    @param    wireact -- the number of the wire already activated
 *    @param    wiresel -- the number of the selected thread
 *    @return   output -- the number of the wire to be activated
 */
int pushbutton::set_wireactive(int wireact, int wiresel){
  int output = wireact; 
  bool _bp2_ni = digitalRead (_BP2_IN);

  // If a change in push-button status is detected 
  if(_bp2_oi != _bp2_ni) {        

    // If the nw value of push-button is 1 (= PRESSED)
    if(_bp2_ni == true){        
      delay(_BP_BOUNCE);   //  We wait for the configuree time to secure the rebound values.
    }

    // If the nw value of push-button is 0 (= RELEASED)
    else if(_bp2_ni == false){
      output = wiresel; 
    }             
    _bp2_oi = _bp2_ni;   //  Set bp2_oi to the current value for the next loop 
  }

  //_wireactive = output; 
  return output; 
}

/** Warns you that a request has been made to save the data on the active feed.
 *    no @param 
 *    @return 0 -- No settings backup requests have been made
 *    @return 1 -- A settings backup has been requested
 */
bool pushbutton::saveButtonActive(){
  bool _bp3_ni = digitalRead (_BP3_IN);
  // If a change in push-button status is detected 
  if(_bp3_oi != _bp3_ni) {        

    // If the nw value of push-button is 1 (= PRESSED)
    if(_bp3_ni == true){        
      delay(_BP_BOUNCE);                     //  We wait for the configuree time to secure the rebound values.
      return 0; 
    }

    // If the nw value of push-button is 0 (= RELEASED)
    else if(_bp3_ni == false){
      return 1; 
    }             
    _bp3_oi = _bp3_ni;                          //  Set bp3_oi to the current value for the next loop 
  } 
}