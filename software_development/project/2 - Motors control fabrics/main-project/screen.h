/* This library is a personal extension of the project, bringing together the functions created to display elements 
 * on the screen at our disposal. This is an extension of the ADAFRUIT libraries. 
 * THE FOLLOWING LIBRARIES ARE REQUIRED FOR IT TO WORK :
 *    > Adafruit_GFX.h
 *    > Adafruit_ST7735.h
 *    > SPI.h
 *
 * DISPLAY REFERENCE :  ADAFRUIT TFT 128*128
 * NUMBER OF PIN :      11 pins
 * BUS COMMUNICATION :  SPI 
 *
 * Created by Marion escouteloup, @maesc on Github
 * Creation date  : 29-06-2023 (DD/MM/YYYY)
 * Last update    :            (DD-MM-YYYY)
 */

#ifndef screen_h
#define screen_h

#include "Arduino.h"
#include <Wire.h>	
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>



void init_screen(); 
void set_fixPrint(); 
void set_clearAllData(uint16_t color = ST77XX_BLACK); 
void testdrawtext(char *text, uint16_t color, int x, int y); 

void set_clearWireData(int choice);
void set_writeWireData(bool act, int active, int select);

void set_clearCurrentData(); 
void set_writeCurrentData(bool act, int current, int poten); 

void set_clearSaveData(int choice); 
void set_writeSaveData(bool act, int activew, int current, int poten); 

#endif