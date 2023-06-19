
#include <Wire.h>
#include "Display4dig7seg.h"

/*** VARIABLE DEFFINITION ***/
#define REFRESH_TIME 100  // Time in ms

/***  PIN DEFINE ***/
#define LIGHT_PIN A0
#define BUTTON    A2
Display4dig7seg Display4dig7seg(9, 8, 7, 6, 5, 4, 3, 13, 12, 11, 10); // pin( a, b, c, d, e, f, g, dgt1, dgt2, dgt3, dgt4)

int i = 0;
int test[5] = {100, 123, 4567, 809, 9990 };



/*** FUNCTION FOR LIGHT INTENSITY **/
int get_lightIntensity() {
  int value = analogRead(A0);
  Serial.println("intensité de 0 a 1023 : " + String(value));
  return value;
}

/*******************************/
/*** VOIIIIIID SETUUUUUUUUUP ***/
/*******************************/
void setup() {
  Serial.begin(115200);
}

/*******************************/
/*** VOIIIIIID LOOOOOOOOOOOP ***/
/*******************************/
void loop() {

  Display4dig7seg.set_digit(0, 0, 0, 0);
  //Serial.println("value before : " + String(test[i]));
  int value = get_lightIntensity();
  for (int a = 0; a < (REFRESH_TIME / 4); a++) {
    Display4dig7seg.print_4digit(value);
    //Display4dig7seg.print_4digit(test[i]);
  }
  Serial.println("light value : " + String(value));


  if (i > 3) (i = 0);
  else (i++);
}