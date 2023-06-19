/*
 * Test code developp for muscle wire test 
 * by Marion Escouteloup
 * @maresc at Github
*/

/***************************/
/***** GLOBAL VARIABLE *****/
/***************************/
/** GLOBAL CONFIGURATION **/ 
#define BAUDRATE 115200

/** GLOBAL PIN CONFIG **/
#define BUTTON_IN 8
#define TEST_OUT  12

/**
 * 
 */
 
 void set_testMuscleWire(){
  Serial.println("Start of muscle wire test ..."); 
  int input = digitalRead(BUTTON_IN); 
  digitalWrite(TEST_OUT, input); 
  
  if(input == 1)
    Serial.println("UP - inital form");
 }

void setup() {
  Serial.begin(BAUDRATE); 
  Serial.println("CONFIGURATION STATUS : in work");
  
  /*** Input pin - init ***/
  pinMode(BUTTON_IN, INPUT); 
  
  /*** Output pin - init ***/
  pinMode(TEST_OUT, OUTPUT);
  
  Serial.println("CONFIGURATION STATUS : ok"); 
}

void loop() {
  set_testMuscleWire(); 
  delay(1); 
    
}
