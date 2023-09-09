/* This library is a personal extension of the project,it is made up of all the pre-designed functions required to implement the various functions. 
 * Thus, this library is composed of :  
 *          --> All the global library used for the execution of the all function and components
 *          --> Deffinition of the pin and declaration of the objects to use the global library 
 *          --> Deffintion of global value and constant 
 *          --> All function created for the projects 
 * THE FOLLOWING LIBRARIES ARE REQUIRED FOR IT TO WORK :
 *    > Adafruit_GFX.h
 *    > Adafruit_ST7735.h
 *    > SPI.h
 *        >>> This library are incclude in the library function.h. Verify to have correctly thuis library to lauch dthe global programm
 *
 * Created by Marion escouteloup, @maesc on Github
 * Creation date  : 21-08-2023 (DD/MM/YYYY)
 * Last update    :            (DD-MM-YYYY) by 
 */

#ifndef terminal_h
#define terminal_h

#include "function.h"
#include <Adafruit_GFX.h>       // ADAFRUIT LIB : to control the LCD SCREEN 128*128 TFT
#include <Adafruit_ST7735.h>    //    >> <Adafruit_GFX.h>  extention
#include <Adafruit_ST77xx.h>    //    >> <Adafruit_GFX.h>  extention


void init_screen();
void testdrawtext(char *text, uint16_t color, int x, int y);
void cleanScreen();

void set_fixTextChoiceScreen();
void set_clearConfigChoiceScreen();
void set_writeConfigChoiceScreen(int ligns, int speed);

void set_fixFabricsScreen(); 
void set_fabricsValue(int ligns); 

void set_fixTextHomeMenu(); 
void set_clearHomeMenuChoice(); 
void set_writeHomeMenuChoice(int choice); 

void set_fixTextDemo1Screen(int nol, int speed);
void set_fixTextDemo2Screen(int nol, int speed);

void set_fixTextAutoScreen(int nol, int speed);
void set_valueAutoMode(int heat, int humidity); 


#endif