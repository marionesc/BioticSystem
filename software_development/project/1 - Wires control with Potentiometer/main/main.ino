/*
 * Test code developp for muscle wire test 
 * by Marion Escouteloup
 * @maresc at Github
 * 
 * Cration day : 06/20/2023 - 10:00am (MM/DD/YYYY)
 * Last update : 06/20/2023 - 00:00am (MM/DD/YYYY)
*/

#include "pushbutton.h"

/**************************************************************************/
/***************            GLOBAL VALUE & PINS             ***************/ 
/**************************************************************************/
// PIN DEFFINITION 
  // INPUT 
    #define BP1_IN          7
    #define BP2_IN          6
    #define BP3_IN          5

    #define CURRENT1_IN     A0
    #define CURRENT2_IN     A1
    #define CURRENT3_IN     A2

    #define POTEN_IN        A3

  // OUTPUT
    #define WIRE1_OUT       11
    #define WIRE2_OUT       10
    #define WIRE3_OUT       9

    #define WIRE1LED_OUT    13
    #define WIRE2LED_OUT    12
    #define WIRE3LED_OUT    8


// GLOBALE VALUE

/**************************************************************************/
/***************         GLOBAL VARIABLE DECLARATION        ***************/ 
/**************************************************************************/
// Variable for fonctions of push-buttons
  pushbutton pushbutton(BP1_IN, BP1_IN, BP1_IN, 50); 

  int wire1carac[] = {0,0}; 
  int wire2carac[] = {0,0}; 
  int wire3carac[] = {0,0}; 
  int wireactive = 1;               // Wire currently active
  int wireselect = 1;               // Wire currently selected (bu not actived for the moment)

  int     cw1, cw2, cw3; 
  int     pw1 , pw2, pw3; 
//

// Variable for wire
  //const int wire[3]     = {WIRE1_OUT, WIRE2_OUT, WIRE3_OUT}; 
  //const int wireled[3]  = {WIRE1LED_OUT, WIRE2LED_OUT, WIRE3LED_OUT}; 

  int wire_s[3]         = {0,0,0}; 
  int wireled_s[3]      = {0,0,0}; 
//

  int poten_oi,poten_ni; 


/**************************************************************************/
/***************              GLOABAL FUNCTION              ***************/ 
/**************************************************************************/

void affichage_debug(int wire, int wires, int current1, int current2, int current3, int poten1, int poten2, int poten3){
  Serial.println("Wire active : " + String(wire));
  Serial.println("Wire select : " + String(wires));
  Serial.println("      DATA WIRE 1 : Current [mA]: " + String(current1) + "    Poten : " + String(poten1)); 
  Serial.println("      DATA WIRE 2 : Current [mA]: " + String(current2) + "    Poten : " + String(poten2)); 
  Serial.println("      DATA WIRE 3 : Current [mA]: " + String(current3) + "    Poten : " + String(poten3)); 
  Serial.println("      \n\n"); 
}


/**************************************************************************/
/***************            SETUP & LOOP PROGRAM            ***************/ 
/**************************************************************************/
void setup() {
  Serial.begin(115200); 

  // INITIALIZATION OF PINS I/O  
    // -- No neccessary for analogic input
  pinMode(WIRE1_OUT, OUTPUT); 
  pinMode(WIRE2_OUT, OUTPUT);
  pinMode(WIRE3_OUT, OUTPUT);

  pinMode(WIRE1LED_OUT, OUTPUT);
  pinMode(WIRE2LED_OUT, OUTPUT);
  pinMode(WIRE3LED_OUT, OUTPUT);

  pushbutton.init_pushButtons(); 

  poten_ni  = digitalRead(POTEN_IN);
}

int cpt = 0; 
int i = 0; 
int vpo = 0; 


void loop() {

  // JUST FOR DEBUUG 
  pw1 = random(0, 1023); 
  pw2 = random(0, 1023); 
  pw3 = random(0, 1023); 

  
  cw1 = random(0, 5000); 
  cw2 = random(0, 5000); 
  cw3 = random(0, 5000); 

  /***************************/
  /*** INPUT DATA RECOVERY ***/
  /***************************/
  // POTENTIOMETER -- reading analogic value
  poten_oi = poten_ni; 
  poten_ni = analogRead(POTEN_IN); 

  // PUSH-BUTTON ONE -- Cable increment launched 
  wireselect = pushbutton.set_wireselect(wireselect);
  
  // PUSH-BUTTON TWO -- Wire activation selected 
  wireactive = pushbutton.set_wireactive(wireactive, wireselect); 
  
  // PUSH-BUTTON THREE -- save the current values of the active wire 
  if(pushbutton.saveButtonActive() == 1){
    switch(wireactive){
      case 1: 
        wire1carac[0] = pw1; 
        wire1carac[1] = cw1; 
        break; 
      
      case 2:
        wire2carac[0] = pw2; 
        wire2carac[1] = cw2; 
        break; 
      
      case 3: 
        wire3carac[0] = pw3; 
        wire3carac[1] = cw3; 
        break; 
      
      default: 
        Serial.println("FATAL ERRORS -- NO CABLE NUMBER IS RECOGNIZED \n\n"); 
    } 
  }
  


  /***************************/
  /***    OUTPUT ACTION    ***/
  /***************************/
  switch(wireactive){
    case 1 : 
      wire_s[0] = poten_ni;     wireled_s[0] = 1; 
      wire_s[1] = 0;            wireled_s[1] = 0;
      wire_s[2] = 0;            wireled_s[0] = 0;
      break; 
    
    case 2 : 
      wire_s[0] = 0;            wireled_s[0] = 0; 
      wire_s[1] = poten_ni;     wireled_s[1] = 1;
      wire_s[2] = 0;            wireled_s[0] = 0;
      break; 

    case 3 : 
      wire_s[0] = 0;            wireled_s[0] = 0; 
      wire_s[1] = 0;            wireled_s[1] = 0;
      wire_s[2] = poten_ni;     wireled_s[0] = 1;
      break; 

    default : 
      wire_s[0] = 0;            wireled_s[0] = 0; 
      wire_s[1] = 0;            wireled_s[1] = 0;
      wire_s[2] = 0;            wireled_s[0] = 0;
      break; 
  }
  analogWrite(WIRE1_OUT, wire_s[0]); 
  digitalWrite(WIRE1LED_OUT, wireled_s[0]); 

  analogWrite(WIRE2_OUT, wire_s[1]); 
  digitalWrite(WIRE2LED_OUT, wireled_s[1]); 

  analogWrite(WIRE3_OUT, wire_s[2]);
  digitalWrite(WIRE3LED_OUT, wireled_s[2]);  

  /***************************/
  /***        DEBUGG       ***/
  /***************************/
  if( i == 100){
    i = 0; 
    affichage_debug(wireactive, wireselect, wire1carac[0], wire2carac[0], wire3carac[0], wire1carac[1], wire2carac[1], wire3carac[1]); 
    Serial.println(cpt + "\n\n");
    cpt++;  
  }
  else{ 
    delay(1); 
    i++; 
  }
}
