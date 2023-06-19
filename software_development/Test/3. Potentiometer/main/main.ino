
#include "potentiometer.h"

#define potenPin  A1
#define ledPin    2
#define potenValue 9999

/*** DEFFINITION ***/
 
/*******************/
void setup(){ 
  Serial.begin(9600);
  Serial.println("Init"); 
}

void loop(){
  Serial.println("bruh"); 
  delay(2000); 
}