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

#include "screen.h"

// LCD PIN DEFFINITION 
#define LCD_CS          53
#define LCD_SCK         52
#define LCD_MOSI        51
#define LCD_MISO        50
#define LCD_RST         49
#define LCD_CCS         48
#define LCD_DC          47

// TIME DEFFINITON


// For ST7735-based displays, we will use this call
Adafruit_ST7735 tft = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_MOSI, LCD_SCK, LCD_RST);

/** @brief Screen initialization steps
 *    > no @param
 *    > no @return 
 */ 
void init_screen(){
  //Serial.println("Initialisation de l'écran");
  
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(1);             // Config the good sreen rotation
  tft.fillScreen(ST77XX_BLACK);   // Background in black

  set_fixPrint();  
  set_clearAllData(ST77XX_BLACK); 
  Serial.println("    >> LCD SCREEN INITIALIZATION : APPROVED");
}

/** @brief Display of items that will not change (blocked items). Called in init_screen() function.  
 *    > no @param
 *    > no @return 
 */ 
void set_fixPrint(){
  char *test = "------- WIRE -------" ; 
  testdrawtext(test , ST77XX_WHITE,   5, 5);
  testdrawtext(" > Active : " ,         ST77XX_WHITE,   5, 15);
  testdrawtext(" > Select : " ,         ST77XX_WHITE,   5, 25);

  testdrawtext("--- CURRENT DATA ---" , ST77XX_GREEN,   5, 45);
  testdrawtext(" > Cur mA : " ,         ST77XX_GREEN,   5, 55);
  testdrawtext(" > Poten  : " ,         ST77XX_GREEN,   5, 65);

  testdrawtext("---- SAVED DATA ----" , ST77XX_RED,     5, 85);
  testdrawtext(" > w1 : " ,             ST77XX_RED,     5, 95);
  testdrawtext(" > w2 : " ,             ST77XX_RED,     5, 105);
  testdrawtext(" > w3 : " ,             ST77XX_RED,     5, 115);
}


/** @brief Cleans all display areas of variable and changing parameters. Called int init_screen() function.
 *    > @param color : The color to be displayed in the display zones varies. 
 *    > no @return 
 */ 
void set_clearAllData(uint16_t color = ST77XX_BLACK){
  // For WIRE CATEGORY
  tft.fillRect(80, 15, 100, 20 , color );

  // For CURRENT DATA CATEGORY
  tft.fillRect(80, 55, 100, 20 , color );

  // For SAVED DATA CATEGORY
  tft.fillRect(80, 95, 100, 60 , color );
}

/** @brief Clean data in wire data category 
 *    > @param choice : '1' clean only active wire, '2' clean only select wire, others, clean all data in wire category
 *    > no @return 
 */ 
void set_clearWireData(int choice){
  switch(choice){
    case 1 :   // clean active wire data
      tft.fillRect(70, 15, 100, 10 , ST77XX_BLACK );   break; 
    case 2 :   // clean selecte wire data 
      tft.fillRect(70, 25, 100, 10 , ST77XX_BLACK );   break; 
    default :   // clear all wire data
      tft.fillRect(70, 15, 100, 20 , ST77XX_BLACK );   break; 
  }
  delay(10); 
}

/** @brief Clean old wire data and write new value
 *    > @param active : the active wire (1 or 2 or 3)
 *    > @param select : the select wire (1 or 2 or 3)
 *    > no @return 
 */ 
void set_writeWireData(bool act, int active, int select){
    char _active[6];  sprintf(_active, "%d", active); 
    char _select[6];  sprintf(_select, "%d", select); 
    
  if(act == true){
    set_clearWireData(3); 
    delay(10); 
    testdrawtext(_active, ST77XX_WHITE, 75, 15); 
    testdrawtext(_select, ST77XX_WHITE, 75, 25); 
  }
}


/** @brief Clean data in current data category --> clean all bc current is dependant of poten value
 *    > no @param
 *    > no @return 
 */ 
void set_clearCurrentData(){
  tft.fillRect(70, 55, 100, 20 , ST77XX_BLACK );
}

/** @brief Clean old current data and write new value
 *    > @param act : boolean true if we need to change the display
 *    > @param current : the current consumption in mA of the curent active wire
 *    > @param poten : the current value of the potentiometer (no units)
 *    > no @return 
 */ 
void set_writeCurrentData(bool act, int current, int poten){
  char _current[10];    sprintf(_current, "%d", current);
  char _poten[4];       sprintf(_poten, "%d", poten); 

  if(act == true){
    set_clearCurrentData(); 
    delay(10); 
    testdrawtext(_current,  ST77XX_WHITE, 75, 55); 
    testdrawtext(_poten,    ST77XX_WHITE, 75, 65); 
  }
}

/** @brief Clean data in current data category --> clean all bc current is dependant of poten value
 *    > no @param
 *    > no @return 
 */ 
void set_clearSaveData(int choice){
   switch(choice){
      case 1 :   // clean only wire 1 saved data 
        tft.fillRect(55, 95, 100, 10 , ST77XX_BLACK );     break; 
      case 2 :  // clean only wire 2 saved data
        tft.fillRect(55, 105, 100, 10 , ST77XX_BLACK );    break; 
      case 3 :  // clean only wire 3 saved data 
        tft.fillRect(55, 115, 100, 10 , ST77XX_BLACK );    break; 
      default : // clean all wire saved data
        tft.fillRect(55, 95, 100, 30 , ST77XX_BLACK );     break;   
   }
}

/** @brief Clean old current data and write new value
 *    > @param act : boolean if we need to change the display
 *    > @param active : the current active wire
 *    > @param current : the current consumption in mA of the curent active wire
 *    > no @return 
 */ 
void set_writeSaveData(bool act, int activew, int current, int poten){
  char _data[15];    sprintf(_data, "%d | %d", current, poten);

  if(act == true){
    switch(activew){
      case 1 : 
        set_clearSaveData(1); delay(10); 
        testdrawtext(_data, ST77XX_WHITE, 60, 95);    break; 

      case 2 : 
        set_clearSaveData(2); delay(10); 
        testdrawtext(_data, ST77XX_WHITE, 60, 105);   break; 

      case 3 : 
        set_clearSaveData(3); delay(10); 
        testdrawtext(_data, ST77XX_WHITE, 60, 115);   break; 

      default:  
        break; 
    } 
  }
}



/** @brief Cleans all display areas of variable and changing parameters. Called int init_screen() function.
 *    > @param text : Text to display
 *    > @param color: Text color code
 *    > @param x : x pixel position
 *    > @param y : y pixel position
 *    > no @return 
 */ 
void testdrawtext(char *text, uint16_t color, int x, int y) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}