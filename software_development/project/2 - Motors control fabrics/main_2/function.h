

/* This library is a personal extension of the project,it is made up of all the pre-designed functions required to implement the various functions. 
 * Thus, this library is composed of :  
 *          --> All the global library used for the execution of the all function and components
 *          --> Deffinition of the pin and declaration of the objects to use the global library 
 *          --> All function created for the projects 
 * THE FOLLOWING LIBRARIES ARE REQUIRED FOR IT TO WORK :
 *    > Adafruit_GFX.h
 *    > Adafruit_ST7735.h
 *    > SPI.h
 *
 * Created by Marion escouteloup, @maesc on Github
 * Creation date  : 18-08-2023 (DD/MM/YYYY)
 * Last update    :            (DD-MM-YYYY)
 */

#ifndef function_h
#define function_h


// >>------------------------------------->>
// >>--- LIBRARY USED FOR THIS PROJECT ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
// >> COMMUN AND OPEN SOUCE LIBRARY
  #include <Wire.h>               // ARDUINO LIB : to control I2C and TWI devices
  #include <Servo.h>              // ARDUINO LIB : to control the servomotors SG90 devices
  #include <Adafruit_GFX.h>       // ADAFRUIT LIB : to control the LCD SCREEN 128*128 TFT
  #include <Adafruit_ST7735.h>    //    >> <Adafruit_GFX.h>  extention
  #include <Adafruit_ST77xx.h>    //    >> <Adafruit_GFX.h>  extention

  #include <DHT11.h>              // DHT11 : library for Temperature and humidity sensor
  #include <HCSR04.h>             // HCSR04: labrary for the proximity and distance sensor
  


// >>---------------------------------------->>
// >>--- FUNCTON CREATED FOR THIS PROJECT ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
  void init_input(); 
  void init_output(int numberLign); 

  int get_pushbuttonUP(int value, int min_value, int max_value ); 
  int get_pushButtonDOWN(int value, int min_value, int max_value ); 
  bool get_pushButtonOK(); 
  bool get_pushButtonHOME(); 
  int get_potenValue(); 

  int get_ambiantHeater(int heat_oi); 
  int get_ambiantHumidity(); 
  int get_proximityDetection(); 
  int get_proxi1(); 
  int get_proxi2();

  int conv_potenToSpeed(); 
  int conv_heatToSpeed(int heat); 

  void set_changeFabrics(int ligns); 
#endif

