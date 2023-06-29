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


// For ST7735-based displays, we will use this call
Adafruit_ST7735 tft = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_MOSI, LCD_SCK, LCD_RST);

/** @brief Screen initialization steps
 *    > no @param
 *    > no @return 
 */ 
void init_screen(){
  int periode = millis(); 
  Serial.println("Initialisation de l'écran");
  
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(1);             // Config the good sreen rotation
  tft.fillScreen(ST77XX_BLACK);   // Background in black

  periode = millis() - periode;
  set_fixPrint();  
  set_clearAllData(ST77XX_BLACK); 
  Serial.println("Initialisation finis. DUREE : " + String(periode) + " ms");
}

/** @brief Display of items that will not change (blocked items). Called in init_screen() function.  
 *    > no @param
 *    > no @return 
 */ 
void set_fixPrint(){
  testdrawtext("------- WIRE -------" , ST77XX_WHITE,   5, 5);
  testdrawtext(" > Active : " ,         ST77XX_WHITE,   5, 15);
  testdrawtext(" > Select : " ,         ST77XX_WHITE,   5, 25);

  testdrawtext("--- CURRENT DATA ---" , ST77XX_GREEN,   5, 45);
  testdrawtext(" > Cur mA : " ,      ST77XX_GREEN,   5, 55);
  testdrawtext(" > Poten  : " ,      ST77XX_GREEN,   5, 65);

  testdrawtext("---- SAVED DATA ----" , ST77XX_RED,     5, 85);
  testdrawtext(" > w1 [mA]: " ,          ST77XX_RED,     5, 95);
  testdrawtext(" > w2 [mA]: " ,          ST77XX_RED,     5, 105);
  testdrawtext(" > w3 [mA]: " ,          ST77XX_RED,     5, 115);
}

/** @brief Cleans all display areas of variable and changing parameters. Called int init_screen() function.
 *    > @param color : The color to be displayed in the display zones varies. 
 *    > no @return 
 */ 
void set_clearAllData(uint16_t color){
  // For WIRE CATEGORY
  tft.fillRect(80, 15, 100, 20 , color );

  // For CURRENT DATA CATEGORY
  tft.fillRect(80, 55, 100, 20 , color );

  // For SAVED DATA CATEGORY
  tft.fillRect(80, 95, 100, 30 , color );
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