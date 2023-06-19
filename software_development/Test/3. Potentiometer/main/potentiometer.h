/* This library has been designed to control and set data with a potentiometer
 *
 * Created by Marion escouteloup, @maesc on Github
 * Last update : 16-06-2023 (DD-MM-YYYY)
 */

#ifndef potentiometer_h
#define potentiometer_h

#include "Arduino.h"
#include <Wire.h>	

class potentiometer{
  public : 
    potentiometer(int potenPin, int pinLed, int potenValue);     
    double get_potentiometer(); 
    void potentiometer_state(bool state); 
    
    int potentiometerStatus; 


  private : 
    int _resolution       = 1024; 
    int _potentPin; 
    int _potenValue; 
    int _ledPin; 
    bool _activePoten     = true;
    bool _inactivePoten   = false;

};

#endif