/* This library is a personal extension of the project,it is made up of all the pre-designed functions required to implement the various functions. 
 * Thus, this library is composed of :  
 *          --> All the global library used to print element on LCD screen by ADAFRUIT

 * THE FOLLOWING LIBRARIES ARE REQUIRED FOR IT TO WORK :
 *    > Adafruit_GFX.h
 *    > Adafruit_ST7735.h
 *    > SPI.h
 *        >>> This library are incclude in the library function.h. Verify to have correctly thuis library to lauch dthe global programm
 *
 * Created by Marion escouteloup, @maesc on Github
 * Creation date  : 21-08-2023 (DD/MM/YYYY)
 * Last update    :            (DD-MM-YYYY)
 */

#include "terminal.h"

// >> SCREEN LCD PIN
#define LCD_CS 53
#define LCD_SCK 52
#define LCD_MOSI 51
#define LCD_MISO 50
#define LCD_RST 47
#define LCD_CCS 48
#define LCD_DC 49

// For ST7735-based displays, we will use this call
Adafruit_ST7735 tft = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_MOSI, LCD_SCK, LCD_RST);




// >>----------------------------->>
// >>--- BASIC SCREEN FUNCTION ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
/** @brief Screen initialization steps
 *    > no @param
 *    > no @return 
 */
void init_screen() {
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);     // Init ST7735S chip, black tab
  tft.setRotation(1);            // Config the good sreen rotation
                                 //tft.fillScreen(ST77XX_RED);   // Background in blue
                                 // tft.fillScreen(ST77XX_WHITE);   // Background in white
                                 // tft.fillScreen(ST77XX_BLUE);   // Background in red
  tft.fillScreen(ST77XX_BLACK);  // Background in black
  Serial.println("    >> LCD SCREEN INITIALIZATION : APPROVED");
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


/** @brief Clear all the LCD screen surface (take all screen in black)
 *    > no @param    
 *    > no @return 
 */
void cleanScreen() {
  tft.fillScreen(ST77XX_BLACK);  // Background in black
}

// >>------------------------------------->>
// >>--- CONFIGURATION SCREEN TERMINAL ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
/** @brief Print the fix text for the configuration terminal
 *    >>  no @param
 *    >> no @return
 */
void set_fixTextChoiceScreen() {
  // Canadian Flag
  tft.fillRect(0, 0, 40, 15, ST77XX_BLUE);
  tft.fillRect(41, 0, 48, 15, ST77XX_WHITE);
  tft.fillRect(89, 0, 40, 15, ST77XX_BLUE);

  // Fix text for the configuration screen
  testdrawtext(" -- CONFIGURATION -- ", ST77XX_WHITE, 5, 30);
  testdrawtext(" >>---------------<< ", ST77XX_WHITE, 5, 45);

  testdrawtext(" > Ligns : ", ST77XX_WHITE, 10, 60);
  testdrawtext(" > Speed : ", ST77XX_WHITE, 10, 80);

  // France Flag
  tft.fillRect(0, 113, 40, 15, ST77XX_RED);
  tft.fillRect(41, 113, 48, 15, ST77XX_WHITE);
  tft.fillRect(89, 113, 40, 15, ST77XX_BLUE);
}

/** @brief Clean old configuration data 
 *    > no @param
 *    > no @return 
 */
void set_clearConfigChoiceScreen() {
  tft.fillRect(80, 60, 50, 20, ST77XX_BLACK);
  tft.fillRect(80, 80, 50, 20, ST77XX_BLACK);
}

/** @brief Clean old wire data and write new value
 *    > @param active : the active wire (1 or 2 or 3)
 *    > @param select : the select wire (1 or 2 or 3)
 *    > no @return 
 */
void set_writeConfigChoiceScreen(int ligns, int speed) {
  char _ligns[6];
  sprintf(_ligns, "%d", ligns);
  char _speed[6];
  sprintf(_speed, "%d", speed);

  set_clearConfigChoiceScreen();
  delay(10);
  testdrawtext(_ligns, ST77XX_WHITE, 80, 60);
  testdrawtext(_speed, ST77XX_WHITE, 80, 80);
}

// >>------------------------------>>
// >>--- GLOABL MENU INTERFACE ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
/**
 *
 */
void set_fixTextHomeMenu() {
  // Magenta squzre around
  tft.fillRect(0, 0, 128, 5, ST77XX_CYAN);
  tft.fillRect(2, 0, 5, 128, ST77XX_CYAN);
  tft.fillRect(128, 0, 5, 128, ST77XX_CYAN);
  tft.fillRect(0, 123, 128, 5, ST77XX_CYAN);

  // Fix text for the configuration screen
  testdrawtext("  -- HOME MENU --  ", ST77XX_WHITE, 5, 25);
  testdrawtext("  >>-----------<<  ", ST77XX_WHITE, 5, 35);

  testdrawtext(" > demo mode 1 ", ST77XX_WHITE, 20, 50);
  testdrawtext(" > demo mode 2 ", ST77XX_WHITE, 20, 65);
  testdrawtext(" > Autom. mode ", ST77XX_WHITE, 20, 80);
  testdrawtext(" > Change Fab. ", ST77XX_WHITE, 20, 95);

  testdrawtext("  >>-----------<<  ", ST77XX_WHITE, 5, 110);
}

/**
 *
 */
void set_clearHomeMenuChoice() {
  tft.fillRect(10, 50, 15, 55, ST77XX_BLACK);
}

/**
 *
 */
void set_writeHomeMenuChoice(int choice) {
  set_clearHomeMenuChoice();
  switch (choice) {
    case 1:  // choice : demo mode 1
      testdrawtext(" 0 ", ST77XX_BLUE, 10, 50);
      break;

    case 2:  // choice : demo mode 2
      testdrawtext(" 0 ", ST77XX_BLUE, 10, 65);
      break;

    case 3:  // choice : automatic mode
      testdrawtext(" 0 ", ST77XX_BLUE, 10, 80);
      break;

    case 4:  // choice : change the fabrics
      testdrawtext(" 0 ", ST77XX_BLUE, 10, 95);
      break;

    default:
      break;
  }
}

void set_fixFabricsScreen() {
  // Magenta square around
  tft.fillRect(0, 0, 128, 5, ST77XX_WHITE);
  tft.fillRect(2, 0, 5, 128, ST77XX_WHITE);
  tft.fillRect(128, 0, 5, 128, ST77XX_WHITE);
  tft.fillRect(0, 123, 128, 5, ST77XX_WHITE);


  testdrawtext("  --- FABRICS ---  ", ST77XX_WHITE, 5, 25);
  testdrawtext("  >>-----------<<  ", ST77XX_WHITE, 5, 35);

  testdrawtext(" > Lign : ", ST77XX_WHITE, 5, 55);
  testdrawtext(" > compress : ", ST77XX_WHITE, 5, 70);
  testdrawtext(" > straight :  ", ST77XX_WHITE, 5, 85);

  testdrawtext("  >>-----------<<  ", ST77XX_WHITE, 5, 105);
}

void set_fabricsValue(int ligns) {

  char _ligns[15];
  sprintf(_ligns, " %d ", ligns);

  tft.fillRect(70, 55, 50, 15, ST77XX_BLACK);
  testdrawtext(_ligns, ST77XX_WHITE, 70, 55);
}
// >>---------------------------->>
// >>--- DEMO SCREEN TERMINAL ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
/** @brief : Screen display during demo no. 1
 *    @param nol : for Nomber Of Ligns 
 *    @param speed : for default speed already configure
 */
void set_fixTextDemo1Screen(int nol, int speed) {
  // Lign to print the number of servomotors ligns already configured
  char _ligns[15];
  sprintf(_ligns, "  > %d ligns ", nol);

  // Default speed to print already configured
  speed = speed * 360;
  char _speed[15];
  sprintf(_speed, "  > %d ms/turn", speed);

  // SCREEN
  // Canadian Flag
  tft.fillRect(0, 0, 40, 15, ST77XX_BLUE);
  tft.fillRect(41, 0, 48, 15, ST77XX_WHITE);
  tft.fillRect(89, 0, 40, 15, ST77XX_BLUE);

  // Fix text for the configuration screen
  testdrawtext("  --  DEMO  ONE  --  ", ST77XX_WHITE, 5, 25);
  testdrawtext("  >>-------------<<  ", ST77XX_WHITE, 5, 35);
  testdrawtext(_ligns, ST77XX_WHITE, 5, 50);
  testdrawtext(_speed, ST77XX_WHITE, 5, 65);
  testdrawtext("  >>-------------<<  ", ST77XX_WHITE, 5, 80);

  testdrawtext(" Please wait the end ", ST77XX_GREEN, 5, 93);
  testdrawtext(" of step to go Home. ", ST77XX_GREEN, 5, 103);

  // France Flag
  tft.fillRect(0, 113, 40, 15, ST77XX_RED);
  tft.fillRect(41, 113, 48, 15, ST77XX_WHITE);
  tft.fillRect(89, 113, 40, 15, ST77XX_BLUE);
}

/** @brief : Screen display during demo no. 2
 *    @param nol : for Nomber Of Ligns 
 *    @param speed : for default speed already configure
 */
void set_fixTextDemo2Screen(int nol, int speed) {
  // Lign to print the number of servomotors ligns already configured
  char _ligns[15];
  sprintf(_ligns, "  > %d ligns ", nol);

  // Default speed to print already configured
  speed = speed * 360;
  char _speed[15];
  sprintf(_speed, "  > %d ms/turn", speed);

  // SCREEN
  // Canadian Flag
  tft.fillRect(0, 0, 40, 15, ST77XX_BLUE);
  tft.fillRect(41, 0, 48, 15, ST77XX_WHITE);
  tft.fillRect(89, 0, 40, 15, ST77XX_BLUE);

  // Fix text for the configuration screen
  testdrawtext("  --  DEMO  TWO  --  ", ST77XX_WHITE, 5, 25);
  testdrawtext("  >>-------------<<  ", ST77XX_WHITE, 5, 35);
  testdrawtext(_ligns, ST77XX_WHITE, 5, 50);
  testdrawtext(_speed, ST77XX_WHITE, 5, 65);
  testdrawtext("  >>-------------<<  ", ST77XX_WHITE, 5, 80);

  testdrawtext(" Please wait the end ", ST77XX_GREEN, 5, 93);
  testdrawtext(" of step to go Home. ", ST77XX_GREEN, 5, 103);

  // France Flag
  tft.fillRect(0, 113, 40, 15, ST77XX_RED);
  tft.fillRect(41, 113, 48, 15, ST77XX_WHITE);
  tft.fillRect(89, 113, 40, 15, ST77XX_BLUE);
}



// >>--------------------------------->>
// >>--- AUTOMATIC SCREEN TERMINAL ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
/** @brief : Screen display during automatic mode
 *    @param nol : for Nomber Of Ligns 
 *    @param speed : for default speed already configure
 */
void set_fixTextAutoScreen(int nol, int speed) {
  // Lign to print the number of servomotors ligns already configured
  char _ligns[15];
  sprintf(_ligns, "  > %d ligns ", nol);

  // Default speed to print already configured
  speed = speed * 360;
  char _speed[15];
  sprintf(_speed, "  > %d ms/turn", speed);

  // Magenta squzre around
  tft.fillRect(0, 0, 128, 5, ST77XX_MAGENTA);
  tft.fillRect(2, 0, 5, 128, ST77XX_MAGENTA);
  tft.fillRect(128, 0, 5, 128, ST77XX_MAGENTA);
  tft.fillRect(0, 123, 128, 5, ST77XX_MAGENTA);

  // Fix text for the configuration screen
  testdrawtext("  --  AUTO MODE  --  ", ST77XX_WHITE, 5, 20);
  testdrawtext("  >>-------------<<  ", ST77XX_WHITE, 5, 30);

  testdrawtext(_ligns, ST77XX_WHITE, 5, 45);
  testdrawtext(_speed, ST77XX_WHITE, 5, 60);
  testdrawtext("  > Heat [C] : ", ST77XX_WHITE, 5, 75);
  testdrawtext("  > Humidity : ", ST77XX_WHITE, 5, 90);

  testdrawtext("  >>-------------<<  ", ST77XX_WHITE, 5, 105);

  //testdrawtext(" Please wait the end ", ST77XX_GREEN, 5, 93);
  //testdrawtext(" of step to go Home. ", ST77XX_GREEN, 5, 103);
}


/**
 *
 */
void set_valueAutoMode(int heat, int humidity) {
  char _heat[10];
  sprintf(_heat, "%d", heat);
  char _humidity[6];
  sprintf(_humidity, "%d", humidity);

  tft.fillRect(80, 75, 40, 25, ST77XX_BLACK);
  testdrawtext(_heat, ST77XX_WHITE, 90, 75);
  testdrawtext(_humidity, ST77XX_WHITE, 90, 90);
}
