  /* This library has been designed to control and set data with a potentiometer
 *
 * Created by Marion escouteloup, @maesc on Github
 * Last update : 16-06-2023 (DD-MM-YYYY)
 */


#include "Arduino.h"
#include <Wire.h>	
#include "potentiometer.h"


/**
 *
 */
potentiometer::potentiometer(int potenPin, int ledPin, int potenValue){
  _potentPin     = potenPin;  
  _potenValue   = potenValue - 1;   
  _ledPin       = ledPin;    

  pinMode(_ledPin, OUTPUT); 

} 


/**
 *
 */
void potentiometer::potentiometer_state(bool state){
  potentiometerStatus = state; 
  digitalWrite(_ledPin, potentiometerStatus);
}

// float resistor = (float(value)/1023) * potenValue + 1 ; 

/**
 *
 */
double potentiometer::get_potentiometer(){
  int value = analogRead(_potentPin);
  double resistor = ((double(value) * (_resolution)) / (_potenValue)) + 1; 
  return resistor; 
}
