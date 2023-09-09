/* 
 * THE FOLLOWING LIBRARIES ARE REQUIRED FOR IT TO WORK :
 *    > terminal.h    -- specific library for this project
 *    > function.h    -- specific library for this project
 *
 * Created by Marion Escouteloup, @maesc on Github
 * Creation date  : 01-08-2023 (DD/MM/YYYY)
 * Last update    : 22-08-2023 (DD-MM-YYYY) by @maesc
 */

//#include "menu.h"
#include "terminal.h"
#include "function.h"

// >>------------------------------>>
// >>--- EXTERN GLOABL CONSTANT ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
extern Servo servoLeft[6];
extern Servo servoRight[6];

const int S_STRAIGHT = 0;
const int S_COMPRESSED = 180;
const int S_DEFAULT = 90;

const int L_MAX = 12;
const int L_MIN = 1;

extern int poten_ni, poten_oi;
int modeChoice = 3;  // in default = automatic mode

// >>------------------------------->>
// >>--- LOCAL VALUE & VARIABLES ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
int number_of_ligns = 1;
int default_speed = 15;


// >>------------------------------->>
// >>--- INTERFACE MODE FUNCTION ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
/** @brief : 
  *    @param 
  *    @return 
  */
void set_configuration() {
  bool ok = 0;
  int nol_oi = number_of_ligns;
  int speed_oi = default_speed;

  bool config = 0;  // '0' : change the number of ligns || '1' change the speed default value


  init_input();
  set_fixTextChoiceScreen();
  set_writeConfigChoiceScreen(nol_oi, speed_oi);

  while (ok != true) {
    ok = get_pushButtonOK();

    //CONFIGURATION OF THE NUMBER OF LIGNS
    number_of_ligns = get_pushbuttonUP(number_of_ligns, 1, 12);  // minimum of lign = 1 || maximum of ligns = 12

    //CONFIGURATION OF THE DEFAULT SPEED VALUE
    default_speed = conv_potenToSpeed();
    // SCREEN REFRESH

    if ((default_speed != speed_oi) || (number_of_ligns != nol_oi)) {
      //Serial.println("lignes = " + String(number_of_ligns) + "  || speed : " + String(default_speed));
      set_writeConfigChoiceScreen(number_of_ligns, default_speed);
      nol_oi = number_of_ligns;
      speed_oi = default_speed;
    }
  }

  init_output(number_of_ligns);
  Serial.println("    >> CONFINGURATION COMPLETED AND APPROVED");
}

/**
 *
 */
void set_menuHome() {
  bool ok = 0;
  int mC_oi = 3;
  set_fixTextHomeMenu();

  while (!ok) {
    // If ok is pressed, current select mode active
    ok = get_pushButtonOK();

    // Select the good mode
    modeChoice = get_pushbuttonUP(modeChoice, 1, 4);

    if ((modeChoice != mC_oi)) {
      set_writeHomeMenuChoice(modeChoice);
      mC_oi = modeChoice;
    }
  }
}


// >>---------------------->>
// >>---  MODE FUNCTION ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
/** @brief : active a demo movement 
  *    @param 
  *    @return 
  */
void demo1_active(int step) {
  switch (step) {
    case 1:
      for (int ligns = 0; ligns < number_of_ligns; ligns++) {
        for (int pos = 90; pos < S_COMPRESSED; pos++) {
          servoLeft[ligns].write(pos);
          servoLeft[ligns].write(pos);
          delay(default_speed);
        }
      }
      break;

    case 2:
      for (int ligns = 0; ligns < number_of_ligns; ligns++) {
        for (int pos = S_COMPRESSED; pos < S_STRAIGHT; pos--) {
          servoLeft[ligns].write(pos);
          servoLeft[ligns].write(pos);
          delay(default_speed);
        }
      }
      break;

    case 3:
      for (int ligns = 0; ligns < number_of_ligns; ligns++) {
        for (int pos = S_STRAIGHT; pos <= S_DEFAULT; pos++) {  // DEFAULT POSITION
          servoLeft[ligns].write(pos);
          servoLeft[ligns].write(pos);
          delay(default_speed);
        }
      }
      break;

    default:
      break;
  }
}

/** @brief : 
  *    @param 
  *    @return 
  */
void demo2_active(int step) {
  switch (step) {
    case 1:
      for (int pos = 90; pos < S_COMPRESSED; pos++) {
        for (int ligns = 0; ligns < number_of_ligns; ligns++) {
          servoLeft[ligns].write(pos);
          servoRight[ligns].write(pos);
          delay(default_speed);
        }
      }
      break;

    case 2:
      for (int pos = S_COMPRESSED; pos < S_STRAIGHT; pos--) {
        for (int ligns = 0; ligns < number_of_ligns; ligns++) {
          servoLeft[ligns].write(pos);
          servoRight[ligns].write(pos);
          delay(default_speed);
        }
      }
      break;

    case 3:
      for (int pos = S_STRAIGHT; pos <= S_DEFAULT; pos++) {  // DEFAULT POSITION
        for (int ligns = 0; ligns < number_of_ligns; ligns++) {
          servoLeft[ligns].write(pos);
          servoRight[ligns].write(pos);
          delay(default_speed);
        }
      }
      break;

    default:
      break;
  }
}

/** @brief : 
  *    @param 
  *    @return 
  */
void automaticMode() {
  Serial.println("Automatical mode active");
}

// >>------------------------------<<
// >>--- MAIN SETUP & MAIN LOOP ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
void setup() {
  Serial.begin(115200);
  Serial.println("  >> START INITIALISATION");
  int init_time = millis();

  // >>------------------------------
  init_screen();
  set_configuration();  // permit to recup the configuration value like the number of ligns



  // >>------------------------------
  init_time = millis() - init_time;
  double init_time2 = (double)init_time / 1000;
  cleanScreen();
  Serial.println("  >> INITIALISATION COMPLETED : " + String(init_time2) + " s");
  Serial.println("  -->> Number of Ligns : " + String(number_of_ligns));
  Serial.println("  -->> Default speed   : " + String(default_speed * 360) + " ms/turn (360°)");
}

bool home = false;

int heat = 0, humidity = 0, detection = 0;
int modeChoice_oi;

unsigned long time = 0;

void loop() {
  set_menuHome();

  while (!home) {
    // Read all input all the 2 seconde
    home = get_pushButtonHOME();

    if ((millis() - time) > 2000) {
      heat = get_ambiantHeater(heat);
      humidity = get_ambiantHumidity();
      detection = get_proximityDetection();
      time = millis();
    }

    if (modeChoice != modeChoice_oi) {
      cleanScreen();
      modeChoice_oi = modeChoice; 
    }

    switch (modeChoice) {
      // DEMO MODE 1
      case 1:
        set_fixTextDemo1Screen(number_of_ligns, default_speed);
        for (int step = 1; step <= 3; step++) {
          demo1_active(step);
        }
        break;
      case 2:  // actie demo mode 2
        set_fixTextDemo1Screen(number_of_ligns, default_speed);
        for (int step = 1; step <= 3; step++) {
          demo2_active(step);
        }
        break;
      case 3:  // active sensor mode active
        set_fixTextAutoScreen(number_of_ligns, default_speed); 
        set_valueAutoMode(heat,humidity);
        break;
      case 4:  // add or change the fabrics
        set_fixFabricsScreen(); 
        
        for (int lignss = 0; lignss < number_of_ligns; lignss++) {
          bool okChange = false;
          set_changeFabrics(lignss);
          while (!okChange) {
            okChange = get_pushButtonOK();
          }
          set_fabricsValue(lignss); 
        }
        break;
      default:
        break;
    }
  }
}