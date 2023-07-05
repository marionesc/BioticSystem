

/*
 * Test code developp for muscle wire test 
 * by Marion Escouteloup
 * @maresc at Github
 * 
 * Cration day : 06/20/2023 - 10:00am (MM/DD/YYYY)
 * Last update : 06/30/2023 -  4:00pm (MM/DD/YYYY)
*/

/**************************************************************************/
/***************       LIBARARY USED FOR THIS PROJEC T      ***************/ 
/**************************************************************************/
/*** COMMUN AND OPEN SOUCE LIBRARY ***/
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>          // Library for de LCD Screen TFT 128*128 by Adafruit
#include <Adafruit_ST77xx.h>
#include <ACS712.h>                   // Library for Current Sensor 
#include <Servo.h>

/*** PERSONNAL LIBRARY (LIBRARY WITH CLASS OR EXTENDED LIBRARY) ***/
#include "screen.h"                   // Extended library of ADAFRUIT_ST7735.h and ADAFRUIT_GFX.h 
#include "pushbutton.h"               // Library created for push button control 


char* nb1 = "100"; 
char* nb2 = "985"; 

/**************************************************************************/
/***************     INDIVIDUAL DEFFINITION AND FUNCTION    ***************/ 
/**************************************************************************/
  #define TIME_TO_DISPLAY   1000    //Display update each 500 ms
  #define TIME_TO_SERVO     5       // Servo change pos each 5 ms
  #define TIME_TO_RESET     60000   // Time to reset and clean LCD screen 

  unsigned long timeloop          = 0; 
  unsigned long displayTimer      = 0; 
  unsigned long displayTime       = 0; 
  unsigned long displayReset      = 0; 
  unsigned long displayRstTimer   = 0; 

  unsigned long servoTimer        = 0; 
  unsigned long servoTime         = 0; 

  /***************              PUSH-BUTTONS              ***************/  
    /***  pin for push-buttons circuit ***/
      #define BP1_IN          26
      #define BP2_IN          24
      #define BP3_IN          22
    /***  variable for push-buttons calibration and class def. ***/  
      pushbutton pushbutton(BP1_IN, BP2_IN, BP3_IN, 50); 

      int wireactive = 1;               // Wire currently active
      int wireselect = 1;               // Wire currently selected (bu not actived for the moment) 

      bool wiresave  = false; 
      bool changeWD  = false; 
      bool changeCD  = false; 
      bool changeSave= false; 

      int wireactive_oi, wireselect_oi;
      bool wiresave_oi; 
  /**/                                                                /**/

  /***************              POTENTIOMETER             ***************/
    /***  pin for potentiometer ***/
      #define POTEN_IN  A0

    /***  constant and variable for potentiometer ***/
      int poten_oi = 0; 
      int poten_ni = 0; 

      int potenSave[] = {0,0,0}; 
  /**/                                                                /**/

  /***************             CURRENT SENSOR             ***************/ 
    /*** pin for current sensors ***/
      #define CURRENT1_IN     A1
      #define CURRENT2_IN     A2
      #define CURRENT3_IN     A3

    /***  constante for current sensor calibration and class def. ***/  
      #define PRECISION_C   185
      #define PRECISION_ADC 1023
      #define VOLTAGE_ADC   5.0

      ACS712 AC1(CURRENT1_IN, VOLTAGE_ADC, PRECISION_ADC, PRECISION_C); 
      ACS712 AC2(CURRENT2_IN, VOLTAGE_ADC, PRECISION_ADC, PRECISION_C); 
      ACS712 AC3(CURRENT3_IN, VOLTAGE_ADC, PRECISION_ADC, PRECISION_C);  

      int current[3]       = {0,0,0}; 
      int currentSave[3]   = {0,0,0}; 
    
    /***  Function for the current sensor reading ***/ 
      void init_currentSensor(){ 
        AC1.autoMidPoint();
        AC2.autoMidPoint();
        AC3.autoMidPoint();
        
        delay(1000);
        Serial.println("    >> CURRENT SENSORS INITIALIZATION : APPROVED"); 
      }

      void get_current1(int precision){
        int mA1 = 0; 
        int mA2 = 0; 

        mA1 = AC1.mA_DC(); 
        for(int i = 1; i < precision; i++){
          mA2 = (mA1 + AC1.mA_DC())/2;
          mA1 = mA2; 
          delay(1); 
        }
      }
      
      void get_current2(int precision){
        int mA1 = 0; 
        int mA2 = 0; 

        mA1 = AC2.mA_DC(); 
        for(int i = 1; i < precision; i++){
          mA2 = (mA1 + AC2.mA_DC())/2;
          mA1 = mA2; 
          delay(1); 
        }
      }
      
      void get_current3(int precision){
        int mA1 = 0; 
        int mA2 = 0; 

        mA1 = AC3.mA_DC(); 
        for(int i = 1; i < precision; i++){
          mA2 = (mA1 + AC3.mA_DC())/2;
          mA1 = mA2; 
          delay(1); 
        }
      }

  /**/                                                                /**/

  /***************        WIRE CONTROL AND WIRE LED       ***************/
    /*** pin for wire and wire led control ***/  
      #define WIRE1_OUT       46
      #define WIRE2_OUT       45
      #define WIRE3_OUT       44

      #define WIRE1LED_OUT    28
      #define WIRE2LED_OUT    30
      #define WIRE3LED_OUT    32
    /*** constant and variable for the wire control and wire led ***/
    /*** function for wire control and wire led ***/
      void init_wire(){
        pinMode(WIRE1_OUT, OUTPUT);     digitalWrite(WIRE1_OUT, 0); 
        pinMode(WIRE2_OUT, OUTPUT);     digitalWrite(WIRE2_OUT, 0); 
        pinMode(WIRE3_OUT, OUTPUT);     digitalWrite(WIRE3_OUT, 0); 

        pinMode(WIRE1LED_OUT, OUTPUT);  digitalWrite(WIRE1LED_OUT, 1);
        pinMode(WIRE2LED_OUT, OUTPUT);  digitalWrite(WIRE2LED_OUT, 1);
        pinMode(WIRE3LED_OUT, OUTPUT);  digitalWrite(WIRE3LED_OUT, 1);
        
        delay(1000);
        Serial.println("    >> WIRE AND WIRE LED INITIALIZATION : APPROVED"); 

      }
      void set_led(bool led1, bool led2, bool led3){
        digitalWrite(WIRE1LED_OUT, led1);
        digitalWrite(WIRE2LED_OUT, led2);
        digitalWrite(WIRE3LED_OUT, led3);
      }
      
      void set_wireled(int wa){
        switch(wa){
          case 1 : 
            set_led(1,0,1);   break; 
          case 2 : 
            set_led(0,1,0);   break; 
          case 3 : 
            set_led(0,0,1);   break; 
          default : 
            set_led(1,1,1);   break;
        }
      }

      
  /**/                                                                /**/

  /***************               SERVOMOTORS              ***************/
    /***  pin for servomotors control ***/ 
      #define SERVOW1_OUT     5
      #define SERVOW2_OUT     6
      #define SERVOW3_OUT     7

    /*** variable and object deffintion for servomotors control ***/

      Servo servo1; 
      Servo servo2; 
      Servo servo3;

    /*** function for servomotors ***/
      void init_servo(){
        servo1.attach(SERVOW1_OUT); 
        servo2.attach(SERVOW2_OUT);
        servo3.attach(SERVOW3_OUT);

        int pos = 0; 

        // Servo 1 
        for (pos = 0; pos <= 180; pos += 1) {
          servo1.write(pos); delay(5); }
        for (pos = 180; pos >= 0; pos -= 1) { 
          servo1.write(pos); delay(5); }
        delay(500); 

        // Servo 2 
        for (pos = 0; pos <= 180; pos += 1) {
          servo2.write(pos); delay(5); }
        for (pos = 180; pos >= 0; pos -= 1) { 
          servo2.write(pos); delay(5); }
        delay(500); 

        // Servo 3 
        for (pos = 0; pos <= 180; pos += 1) {
          servo3.write(pos); delay(5); }
        for (pos = 180; pos >= 0; pos -= 1) { 
          servo3.write(pos); delay(5); }
        delay(500); 

        Serial.println("    >> SERVOMOTORS INITIALIZATION : APPROVED"); 
      }

      void set_servo(int wa, int speedTime = 20){
        int pos1 = servo1.read(); 
        int pos2 = servo2.read(); 
        int pos3 = servo3.read(); 

        switch(wa){
          case 1 :
            for(pos1; pos1 < 180; pos1++){ // Active Wire
              servo1.write(pos1); 
              delay(speedTime); 
            }
            for(pos2; pos2 > 0; pos2--){ // Inactive wire
              servo3.write(pos2); 
              delay(speedTime); 
            }
            for(pos3; pos3 > 0; pos3--){ // Inactive wire
              servo3.write(pos3); 
              delay(speedTime); 
            }

            break; 
            
          case 2 :
            for(pos1; pos1 > 0; pos1--){ // Active Wire
              servo1.write(pos1); 
              delay(speedTime); 
            }
            for(pos2; pos2 < 180; pos2++){ // Inactive wire
              servo2.write(pos2); 
              delay(speedTime); 
            }
            
            for(pos3; pos3 > 0; pos3--){ // Inactive wire
              servo3.write(pos3); 
              delay(speedTime); 
            }

            break; 
            
          case 3 :
            for(pos1; pos1 > 0 ; pos1--){ // Active Wire
              servo1.write(pos1); 
              delay(speedTime); 
            }
            for(pos2; pos2 > 0; pos2--){ // Inactive wire
              servo2.write(pos2); 
              delay(speedTime); 
            }
            
            for(pos3; pos3 < 180 ; pos3++){ // Inactive wire
              servo3.write(pos3); 
              delay(speedTime); 
            }

            break;
          
          default : 
            for(pos1; pos1 > 0 ; pos1--){ // Active Wire
              servo1.write(pos1); 
              delay(speedTime); 
            }

            for(pos2; pos2 > 0; pos2--){ // Inactive wire
              servo2.write(pos2); 
              delay(speedTime); 
            }
            
            for(pos3; pos3 > 0 ; pos3--){ // Inactive wire
              servo3.write(pos3); 
              delay(speedTime); 
            }
            break;  
        }
      }
  /**/                                                                /**/

  /***************       DEBUGG VARIABLE AND FUNCTION     ***************/
    /*** debugg variable and constant ***/ 
      int j = 0; 
      int cpt = 0; 
      int i = 0; 
      int vpo = 0; 

    /*** debugg function ***/
      void affichage_debug(int wire, int wires, int current1, int current2, int current3, int poten1, int poten2, int poten3){
        Serial.println("Wire active : " + String(wire));
        Serial.println("Wire select : " + String(wires));
        Serial.println("      DATA WIRE 1 : Current [mA]: " + String(current1) + "    Poten : " + String(poten1)); 
        Serial.println("      DATA WIRE 2 : Current [mA]: " + String(current2) + "    Poten : " + String(poten2)); 
        Serial.println("      DATA WIRE 3 : Current [mA]: " + String(current3) + "    Poten : " + String(poten3)); 
        Serial.println("      \n\n"); 
      }


  /**/                                                                /**/

void set_wire(int wa, int poten){
  poten = int(poten / 4); 
  switch(wa){
    case 1 :
      set_wireled(wa); 
      set_servo(wa, 5);
      digitalWrite(WIRE1_OUT, poten); // ON 
      digitalWrite(WIRE2_OUT, 0);     // OFF
      digitalWrite(WIRE3_OUT, 0);     // OFF
      break; 

    case 2 : 
      set_wireled(wa); 
      set_servo(wa, 5);
      digitalWrite(WIRE1_OUT, 0);     // OFF
      digitalWrite(WIRE2_OUT, poten); // ON
      digitalWrite(WIRE3_OUT, 0);     // OFF
      break; 

    case 3 : 
      set_wireled(wa); 
      set_servo(wa, 5);
      digitalWrite(WIRE1_OUT, 0);     //OFF
      digitalWrite(WIRE2_OUT, 0);     //OFf
      digitalWrite(WIRE3_OUT, poten); //ON
      break; 

    default : 
      set_wireled(wa); 
      set_servo(wa);
      digitalWrite(WIRE1_OUT, 0);     //OFF
      digitalWrite(WIRE2_OUT, 0);     //OFF
      digitalWrite(WIRE3_OUT, 0);     //OF
      break; 
  }
}
/**************************************************************************/
/***************            SETUP & LOOP PROGRAM            ***************/ 
/**************************************************************************/

void setup() {
  Serial.begin(115200); 
  Serial.println("INITIALIZATION'S START >> ... "); 

  // MEASURE TIME START
  timeloop = millis(); 


  // INITIALIZATION OF PINS I/O -- No neccessary for analogic input
  init_wire(); 
  init_currentSensor(); 
  init_screen(); 
  pushbutton.init_pushButtons(); 
  init_servo(); 

  poten_ni  = analogRead(POTEN_IN);
  // END OF THE INITIALIZATION 

  // MEASURE TIME END
  timeloop = millis() - timeloop; 
  double time = timeloop / 1000; 

  Serial.println("INITIALIZATION'S END >> ...  " + String(time) + " s"); 
  Serial.println("\n\n");

  set_writeWireData(true, wireactive, wireselect);
  set_writeCurrentData(true, current[wireactive-1], poten_ni);
}


void loop() { 
  timeloop = millis() - timeloop;     // Permit program timer

// DATA INPUT   >--------------------------------------------------------------------------------------------------->
  // DATA INPUT -- Push-button 
    // No timer, we read the buttons on every loop so we never miss a press.
    wireselect_oi = wireselect; 
    wireselect  = pushbutton.set_wireselect(wireselect); 

    wireactive_oi = wireactive; 
    wireactive  = pushbutton.set_wireactive(wireactive, wireselect);  
    
    wiresave_oi = wiresave; 
    wiresave    = pushbutton.saveButtonActive(); 

  // DATA INPUT -- Potentiometer 
    poten_oi = poten_ni;
    poten_ni = analogRead(POTEN_IN); 

  // DATA INPUT -- Current Sensor reading
    // No timer, we read the sensor each time to made average value for more precisions
    current[0] = int(AC1.mA_DC());
    current[1] = int(AC2.mA_AC()); 
    current[2] = int(AC3.mA_AC()); 



// PROGRAMM     >--------------------------------------------------------------------------------------------------->
  // PROGRAMM -- to active the good wire
    set_wire(wireactive, poten_ni); 
  
  // PROGRAMM -- Save data of active wire
    if(wiresave == true){
      currentSave[wireactive - 1] = current[wireactive - 1]; 
      potenSave[wireactive - 1] = poten_ni; 
      changeSave = true; 
    }
    else 
      changeSave = false; 

  // PROGRAMM -- to change display or no (WIRE DATA)
    if((wireselect_oi != wireselect) || (wireactive_oi != wireactive))
      changeWD = true; 
    else 
      changeWD = false; 
  
  // PROGRAMM -- to change display or not (CURRENT DATA)
    if(poten_ni != poten_oi)
      changeCD = true;
    else 
      changeCD = false; 

// DATA OUTPUT AND SCREEN DISPLAY >--------------------------------------------------------------------------------->
  // DATA OUTPUT IN DISPLAY AT THE LCD SCREEN -- Current update
    set_writeWireData(changeWD, wireactive, wireselect); 
    displayTime = millis() - displayTimer; 

    if(displayTime > TIME_TO_DISPLAY){
      set_writeCurrentData(changeCD, current[wireactive - 1], poten_ni); 
      set_writeSaveData(changeSave, wireactive, currentSave[wireactive - 1], potenSave[wireactive - 1]);

      changeWD    = false; 
      changeCD    = false; 
      changeSave  = false; 

      displayTimer = millis();   
      
      
  // DATA OUTPUT IN DISPLAY AT THE LCD SCREEN -- Reset the screen after 1 min 
    displayReset = millis() - displayRstTimer; 
    if(displayReset > TIME_TO_RESET){
      set_clearAllData(); 
      set_writeWireData(true, wireactive, wireselect); 
      set_writeCurrentData(true, current[wireactive - 1], poten_ni); 
      set_writeSaveData(true, wireactive, currentSave[wireactive - 1], potenSave[wireactive - 1]); 

      displayRstTimer = millis(); 
    }

  }


}

