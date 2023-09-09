
/*
 * Test code developp for controlled fabrics movments with servomotors
 * by Marion Escouteloup
 * @maresc at Github
 * 
 * Cration day : 07/18/2023 - 10:30am (MM/DD/YYYY)
 * Last update : 07/18/2023 -  4:00pm (MM/DD/YYYY)
*/

/**************************************************************************/
/***************       LIBARARY USED FOR THIS PROJECT       ***************/ 
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
  /**/

/**************************************************************************/
/***************     INDIVIDUAL DEFFINITION AND FUNCTION    ***************/ 
/**************************************************************************/
  /*** TIME CONSTANT & VARIABLES ***/
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
  /**/   

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

      void set_servo(int wa, int speedUp = 20, int speedDown = 20){
        int pos1 = servo1.read(); 
        int pos2 = servo2.read(); 
        int pos3 = servo3.read(); 

        switch(wa){
          case 1 :
            for(pos1; pos1 < 180; pos1++){ // Active Wire
              servo1.write(pos1); 
              delay(speedUp); 
            }
            for(pos2; pos2 > 0; pos2--){ // Inactive wire
              servo3.write(pos2); 
              delay(speedDown); 
            }
            for(pos3; pos3 > 0; pos3--){ // Inactive wire
              servo3.write(pos3); 
              delay(speedDown); 
            }

            break; 
            
          case 2 :
            for(pos1; pos1 > 0; pos1--){ // Active Wire
              servo1.write(pos1); 
              delay(speedDown); 
            }
            for(pos2; pos2 < 180; pos2++){ // Inactive wire
              servo2.write(pos2); 
              delay(speedUp); 
            }
            
            for(pos3; pos3 > 0; pos3--){ // Inactive wire
              servo3.write(pos3); 
              delay(speedDown); 
            }

            break; 
            
          case 3 :
            for(pos1; pos1 > 0 ; pos1--){ // Active Wire
              servo1.write(pos1); 
              delay(speedDown); 
            }
            for(pos2; pos2 > 0; pos2--){ // Inactive wire
              servo2.write(pos2); 
              delay(speedDown); 
            }
            
            for(pos3; pos3 < 180 ; pos3++){ // Inactive wire
              servo3.write(pos3); 
              delay(speedUp); 
            }

            break;
          
          default : 
            for(pos1; pos1 > 0 ; pos1--){ // Active Wire
              servo1.write(pos1); 
              delay(speedDown); 
            }

            for(pos2; pos2 > 0; pos2--){ // Inactive wire
              servo2.write(pos2); 
              delay(speedDown); 
            }
            
            for(pos3; pos3 > 0 ; pos3--){ // Inactive wire
              servo3.write(pos3); 
              delay(speedDown); 
            }
            break;  
        }
      }
  /**/  



void setup() {
  Serial.begin(115200);
  Serial.println("INITIALIZATION'S START >> ... "); 

  // MEASURE TIME START
  timeloop = millis(); 

  // INITIALIZATION OF PINS I/O -- No neccessary for analogic input
  init_screen(); 
  pushbutton.init_pushButtons(); 
  init_servo();   poten_ni  = analogRead(POTEN_IN);
  // END OF THE INITIALIZATION 

  // MEASURE TIME END
  timeloop = millis() - timeloop; 
  double time = timeloop / 1000; 

  Serial.println("INITIALIZATION'S END >> ...  " + String(time) + " s \n\n")); 
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
