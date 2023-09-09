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
 *
 * Created by Marion escouteloup, @maesc on Github
 * Creation date  : 18-08-2023 (DD/MM/YYYY)
 * Last update    :            (DD-MM-YYYY)
 */

#include "function.h"

// >>--------------------------------------->>
// >>--- PIN DEFFINTION FOR THIS PROJECT ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
// >> SCREEN PIN : directly in screen.cpp library (lign 20.)
// >> INPUT PIN
#define IN_POTEN A0

#define IN_BP1_UP 23
#define IN_BP2_DOWN 25
#define IN_BP3_OK 27
#define IN_BP4_HOME 29

#define IN_THS 33

#define IN_PROX1_TRIG 17  // place on RX2
#define IN_PROX1_ECHO 16  // place on TX2
#define IN_PROX2_TRIG 15  // place on RX3
#define IN_PROX2_ECHO 14  // place on TX3


// >> OUTPUT PIN
#define OUT_SERVO1 4
#define OUT_SERVO2 5
#define OUT_SERVO3 3
#define OUT_SERVO4 6
#define OUT_SERVO5 2
#define OUT_SERVO6 7
#define OUT_SERVO7 8
#define OUT_SERVO8 13
#define OUT_SERVO9 9
#define OUT_SERVO10 12
#define OUT_SERVO11 10
#define OUT_SERVO12 11

int servoLeftPin[6] = { OUT_SERVO1, OUT_SERVO3, OUT_SERVO5, OUT_SERVO7, OUT_SERVO9, OUT_SERVO11 };
int servoRightPin[6] = { OUT_SERVO2, OUT_SERVO4, OUT_SERVO6, OUT_SERVO8, OUT_SERVO10, OUT_SERVO12 };


#define OUT_LR1 22
#define OUT_LR2 26
#define OUT_LR3 30
#define OUT_LR4 34
#define OUT_LC1 24
#define OUT_LC2 28
#define OUT_LC3 32
#define OUT_LC4 36

int ledRedPin[4] = { OUT_LR1, OUT_LR2, OUT_LR3, OUT_LR4 };
int ledColoredPin[4] = { OUT_LC1, OUT_LC2, OUT_LC3, OUT_LC4 };



// >> RTC CLOCK
#define RTC_SDA 20
#define RTC_SCL 21

// >> GLOBAL CLASS DEFFINTION
// servomotor
Servo s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12;
Servo servoLeft[6] = { s1, s3, s5, s7, s9, s11 };
Servo servoRight[6] = { s2, s4, s6, s8, s10, s12 };

// DHT11 : Temperature and humidity sensor
DHT11 ths(IN_THS);

// HC-SR04 : proximity sensor
UltraSonicDistanceSensor prox1(IN_PROX1_TRIG, IN_PROX1_ECHO);
UltraSonicDistanceSensor prox2(IN_PROX2_TRIG, IN_PROX2_ECHO);

int prox1_config = 0;
int prox2_config = 0;

// Push-button
#define BP_BOUNCE 50

//
// >>-------------------------------->>
// >>---GLOBAL VALUE AND CONSTANT ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
const int SPEED_MAX = 1;  //1ms beetween each 1 degre movment
const int SPEED_MIN = 40;
const int SPEED_INIT = 5;

const int S_STRAIGHT = 0;
const int S_COMPRESSED = 180;
const int S_DEFAULT = 90;

//int NUMBER_OF_LIGN = 1;
int poten_ni, poten_oi;

// >>---------------------------------------->>
// >>--- FUNCTON CREATED FOR THIS PROJECT ---<<
// >>-------------------------------------------------------------------------------------------------------------<<
// >> INIT FUNCTION
/** @brief : Initialization of all input ( 4 push-button, 1 potentiometer, 1 THsensor, 2 proximity sensor)
   *  no @param
   *  no @return
   */
void init_input() {
  // init push-button
  pinMode(IN_BP1_UP, INPUT);
  pinMode(IN_BP2_DOWN, INPUT);
  pinMode(IN_BP3_OK, INPUT);
  pinMode(IN_BP4_HOME, INPUT);

  // INIT POTENTIOMETER
  pinMode(IN_POTEN, INPUT);
  poten_ni = analogRead(IN_POTEN);

  // init Temperature en humidity sensor DHT11

  // init proximity sensors
  prox1_config = prox1.measureDistanceCm();
  prox2_config = prox2.measureDistanceCm();
  Serial.println("      >> -- Wall distance in prox1 : " + String(prox1_config) + "cm \n      >> -- Wall distance in prox2 : " + String(prox2_config) + " cm");

  Serial.println("    >> INITIALIZATION OF ALL INPUTS : approved");
}

/** @brief : Initialization of all outputs (4 red leds, 0 to 12 servomotors (depends of real number of servomotors))
 *    no @param
 *    no @return
 */
void init_output(int numberLign) {
  // init led
  pinMode(OUT_LR1, OUTPUT);
  pinMode(OUT_LR2, OUTPUT);
  pinMode(OUT_LR3, OUTPUT);
  pinMode(OUT_LR4, OUTPUT);
  pinMode(OUT_LC1, OUTPUT);
  pinMode(OUT_LC2, OUTPUT);
  pinMode(OUT_LC3, OUTPUT);
  pinMode(OUT_LC4, OUTPUT);

  //init servomotors
  for (int i = 0; i < numberLign; i++) {
    servoRight[i].attach(servoRightPin[i]);
    servoLeft[i].attach(servoLeftPin[i]);

    // All servomotors are positioned in 90°
    int right = servoRight[i].read();
    if (right <= 90 && right >= 0) {
      servoRight[i].write(right);
      right++;
      delay(SPEED_INIT);
    } else if (right > 90 && right <= 180) {
      servoRight[i].write(right);
      right--;
      delay(SPEED_INIT);
    }

    int left = servoRight[i].read();
    if (left <= 90 && left >= 0) {
      servoRight[i].write(right);
      left++;
      delay(SPEED_INIT);
    } else if (left > 90 && left <= 180) {
      servoLeft[i].write(left);
      left--;
      delay(SPEED_INIT);
    }
  }
}


// >>INPUT VALUE FUNCTION
/** @brief : This function is used to configure the number of servomotor lines present on the tray. 
 *           If the maximum value configured in the main program (normally 12) is exceeded, it returns to 1.
 *    @param value 
 *    @param max_value 
 *    @param min_value
 *    @return value 
 */
int get_pushbuttonUP(int value, int min_value, int max_value) {

  bool bp1_ni = digitalRead(IN_BP1_UP);
  // If a change in push-button status is detected
  if (!bp1_ni) {
    delay(BP_BOUNCE);  //  We wait for the configuree time to secure the rebound values.
    bp1_ni = digitalRead(IN_BP1_UP);

    if (bp1_ni) {
      value = value + 1;
      if (value > max_value)
        value = min_value;
      //Serial.println("Valeur lign : " + String(value));
    }
    return value;
  }
}


// >> NO WORK INSIDE THE MAIN CODE --> idk why
/** @brief : 
 *    @param value 
 *    @param max_value 
 *    @param min_value
 *    @return value 
 */
int get_pushButtonDOWN(int value, int min_value, int max_value) {
  bool bp2_ni = digitalRead(IN_BP2_DOWN);

  if (bp2_ni) {
    delay(BP_BOUNCE);  //  We wait for the configuree time to secure the rebound values.
    bp2_ni = digitalRead(IN_BP2_DOWN);

    if (!bp2_ni) {
      value = value - 1;
      if (value < min_value)
        value = min_value;
      Serial.println("Valeur lign : " + String(value));
    }
    return value;
  }
}


/** @brief : 
 *
 */
bool get_pushButtonOK() {
  bool bp3_ni = digitalRead(IN_BP3_OK);

  // If a change in push-button status is detected
  if (bp3_ni) {
    delay(BP_BOUNCE);  //  We wait for the configuree time to secure the rebound values.
    bp3_ni = digitalRead(IN_BP3_OK);
    if (!bp3_ni)
      return true;
  } else
    return false;
}

/** @brief : 
 *
 */
bool get_pushButtonHOME() {
  bool bp4_ni = digitalRead(IN_BP4_HOME);

  // If a change in push-button status is detected
  if (bp4_ni) {
    delay(BP_BOUNCE);  //  We wait for the configuree time to secure the rebound values.
    bp4_ni = digitalRead(IN_BP4_HOME);
    if (!bp4_ni)
      return true;
  } else
    return false;
}

/** @brief :
 *
 */
int get_potenValue() {
  int poten = analogRead(IN_POTEN);
  return poten;
}
/** @brief : Read and return the value of the ambiant temperature in degre Celsus
 *      no @param 
 *      @return heat - the ambiant temperature in °C, always between 0 and 50 °C
 */
int get_ambiantHeater(int heat_oi) {
  float temperature = ths.readTemperature();
  if (temperature == -1) {
    Serial.println("DEBUGG --> Temperature Sensor ERRORS");
    return -1;
  } else
    return (int)temperature;
}

/** @brief : Read and return the percent of the ambiant heater
 *      no @param 
 *      @return humidity - the ambiant humidity range in %
 */
int get_ambiantHumidity() {
  float humidity = ths.readHumidity();
  if (humidity == -1) {
    Serial.println("DEBUGG --> Temperature Sensor ERRORS");
  } else
    return humidity;
}

int get_proxi1() {
  int value = prox1.measureDistanceCm();
  return value;
}

int get_proxi2() {
  int value = prox2.measureDistanceCm();
  return value;
}

/** @brief : Active de proxitimy senso and detect if seomeone move in fornt of the system
 *      no @param 
 *      @return move : '0' for no movement, '1' for a movement on right to left, '2' for a movement left to right
 */
int get_proximityDetection() {
  int time1 = 0;
  int time2 = 0;
  int prox1_distance = prox1.measureDistanceCm();
  int prox2_distance = prox2.measureDistanceCm();

  // READING
  if ((prox1_distance > 10) && (prox1_distance <= (prox1_config - 10))) {  // we detect a mouvement in prox1
    time1 = millis();
  }

  if ((prox2_distance > 10) && (prox2_distance <= (prox2_config - 10))) {  // we detect a mouvement in prox2
    time2 = millis();
  }

  // RETURN
  if ((time1 < time2) && (time1 != 0) && (time2 != 0)) {  // if we detect something in prox1 and after in proxi2 --> movement prox 1 in prox2
    return 1;
  } else if ((time1 > time2) && (time1 != 0) && (time2 != 0)) {  // if we detect something in prox2 and after in proxi1 --> movement prox2 in prox1
    return 2;
  } else {  // else no movement
    return 0;
  }
}


// >> CONVERSION AND TRAITMENT VALUE
/** @brief : This function converts the input value of the potentiometer (0 to 1023) to the value of the speed of movement of the servomotors
 *      no @param
 *      @return speed : the speed at which the servomotors move 
 */
int conv_potenToSpeed() {
  int poten = analogRead(IN_POTEN);
  int speed = map(poten, 0, 1023, SPEED_MIN, SPEED_MAX);
  return speed;
}

/** @brief : Convert the ambiant temperature in a speed value
 *      @param heat : tthe current ambiant temperature
 *      @return speed : the speed at which the servomotors move 
 */
int conv_heatToSpeed(int heat) {
  int temperature = get_ambiantHeater(heat);
  int speed = map(temperature, 0, 50, SPEED_MIN, SPEED_MAX);
  return speed;
}

int servoTime = 0;

void set_changeFabrics(int ligns) {
  int speed = 5;
  bool ok = false;



  for (int pos = S_DEFAULT; pos >= S_STRAIGHT; pos--) {
    servoRight[ligns].write(pos);
    servoLeft[ligns].write(pos);
    delay(speed);
  }


  for (int pos = S_STRAIGHT; pos <= S_COMPRESSED; pos++) {
    servoRight[ligns].write(pos);
    servoLeft[ligns].write(pos);
    delay(speed);
  }

  while (!ok) {
    ok = get_pushButtonOK();
  }


  for (int pos = S_COMPRESSED; pos >= S_DEFAULT; pos--) {
    servoRight[ligns].write(pos);
    servoLeft[ligns].write(pos);
    delay(speed);
  }

  while (!ok) {
    ok = get_pushButtonOK();
  }
}