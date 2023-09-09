#include <ACS712.h>

#define PRECISION_C   185
#define PRECISION_ADC 1023
#define VOLTAGE_ADC   5.0
#define CURRENT_IN    A1

ACS712 AC1(CURRENT_IN, VOLTAGE_ADC, PRECISION_ADC, PRECISION_C); 



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 

  //Init Current 
  AC1.autoMidPoint();
  Serial.println("INITIALISATION!");  

}

  int mA1 = 0; 
  int mA2 = 0; 

void loop() {
  // put your main code here, to run repeatedly:
  mA1  = AC1.mA_DC();

  for(int i = 1; i < 200; i++){
    mA2 = (mA1 + AC1.mA_DC())/2;
    mA1 = mA2;  
    delay(5); 
  }
  //mA = int(mA / 1000); */
  Serial.println("Courant [mA] : " + String(mA2));
  //delay(900); 
 
}
