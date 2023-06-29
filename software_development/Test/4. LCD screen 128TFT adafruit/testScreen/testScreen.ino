#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>


#define LCD_CS          53
#define LCD_SCK         52
#define LCD_MOSI        51
#define LCD_MISO        50
#define LCD_RST         49
#define LCD_CCS         48
#define LCD_DC          47


// For ST7735-based displays, we will use this call
Adafruit_ST7735 tft = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_MOSI, LCD_SCK, LCD_RST);


void setup() {
  uint16_t time = millis();

  // put your setup code here, to run once:
  Serial.begin(115200); 
  init_screen(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  set_fixPrint(); 
  
  set_clearAllData(ST77XX_BLACK); 
  delay(1000); 

  // print random things
  testdrawtext("1" ,       ST77XX_WHITE,   80, 15);
  testdrawtext("3" ,       ST77XX_WHITE,   80, 25);

  testdrawtext("1120 " ,   ST77XX_GREEN,   80, 55);
  testdrawtext("359  " ,   ST77XX_GREEN,   80, 65);

  testdrawtext("120 " ,   ST77XX_RED,     80, 95);
  testdrawtext("1385 " ,   ST77XX_RED,     80, 105);
  testdrawtext("2864 " ,   ST77XX_RED,     80, 115);
  delay(1000); 

  set_clearAllData(ST77XX_RED); 
  delay(1000); 

}

void init_screen(){
  int periode = millis(); 
  Serial.println("Initialisation de l'écran");
  
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(1);             // Config the good sreen rotation
  tft.fillScreen(ST77XX_BLACK);   // Background in black

  periode = millis() - periode; 
  Serial.println("Initialisation finis. DUREE : " + String(periode) + " ms");
}

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

void set_clearAllData(uint16_t color){
  // For WIRE CATEGORY
  tft.fillRect(80, 15, 100, 20 , color );

  // For CURRENT DATA CATEGORY
  tft.fillRect(80, 55, 100, 20 , color );

  // For SAVED DATA CATEGORY
  tft.fillRect(80, 95, 100, 30 , color );
}

void testdrawtext(char *text, uint16_t color, int x, int y) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
