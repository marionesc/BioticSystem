/* This library has been designed to control a 4-digit 7-segment display. It has been verified with a Luckylight display.
 * DISPLAY REFERENCE :  Luckylight L1309088
 * NUMBER OF PIN :      14 pins
 * COMPOSITION :        4 Display of 7 segment (+ segment dot) + digit for ":" print
 *
 * Created by Marion escouteloup, @maesc on Github
 * Last update : 13-06-2023 (DD-MM-YYYY)
 */

#include "Arduino.h"
#include <Wire.h>	
#include "Display4dig7seg.h"

/****************************/
/*** CLASS INITIALIZATION ***/
/****************************/
Display4dig7seg::Display4dig7seg(int seg_a, int seg_b, int seg_c, int seg_d, int seg_e, int seg_f, int seg_g, int dgt_1, int dgt_2, int dgt_3, int dgt_4){
  _seg_a = seg_a;   pinMode(_seg_a, OUTPUT); digitalWrite(_seg_a, 0);   
  _seg_b = seg_b;   pinMode(_seg_b, OUTPUT); digitalWrite(_seg_b, 0);     
  _seg_c = seg_c;   pinMode(_seg_c, OUTPUT); digitalWrite(_seg_c, 0);     
  _seg_d = seg_d;   pinMode(_seg_d, OUTPUT); digitalWrite(_seg_d, 0);
  _seg_e = seg_e;   pinMode(_seg_e, OUTPUT); digitalWrite(_seg_e, 0);
  _seg_f = seg_f;   pinMode(_seg_f, OUTPUT); digitalWrite(_seg_f, 0); 
  _seg_g = seg_g;   pinMode(_seg_g, OUTPUT); digitalWrite(_seg_g, 0);  

  _dgt_1 = dgt_1;   pinMode(_dgt_1, OUTPUT);    digitalWrite(_dgt_1, 1); 
  _dgt_2 = dgt_2;   pinMode(_dgt_2, OUTPUT);    digitalWrite(_dgt_2, 1); 
  _dgt_3 = dgt_3;   pinMode(_dgt_3, OUTPUT);    digitalWrite(_dgt_3, 1); 
  _dgt_4 = dgt_4;   pinMode(_dgt_4, OUTPUT);    digitalWrite(_dgt_4, 1); 

  Serial.println("Display initialization : ok"); }


/* // CLASS WITH DP AND DOT DOT

Display4dig7seg::Display4dig7seg(
  int seg_a, int seg_b, int seg_c, int seg_d, int seg_d, int seg_e, int seg_f, int seg_g, int seg_dp, int seg_dotdot, int dgt_1, int dgt_2, int dgt_3, int dgt_4, int dgt_dotdot){
  _seg_a = seg_a;           pinMode(_seg_a, OUTPUT); 
  _seg_b = seg_b;           pinMode(_seg_b, OUTPUT);  
  _seg_c = seg_c;           pinMode(_seg_c, OUTPUT);  
  _seg_d = seg_d;           pinMode(_seg_d, OUTPUT);
  _seg_e = seg_e;           pinMode(_seg_e, OUTPUT);
  _seg_f = seg_f;           pinMode(_seg_f, OUTPUT);
  _seg_g = seg_g;           pinMode(_seg_g, OUTPUT);
  _seg_dp = seg_dp;         pinMode(_seg_dp, OUTPUT);
  _seg_dotdot = seg_dotdot; pinMode(_seg_dotdot, OUTPUT);

  _dgt_1 = dgt_1;           pinMode(_dgt_1, OUTPUT);
  _dgt_2 = dgt_2;           pinMode(_dgt_2, OUTPUT);
  _dgt_3 = dgt_3;           pinMode(_dgt_3, OUTPUT);
  _dgt_4 = dgt_4;           pinMode(_dgt_4, OUTPUT);
  _dgt_dotdot = dgt_dotdot; pinMode(_dgt_dotdot, OUTPUT);
   
  Serial.println("Display initialization : ok");}
*/

/*****************************/
/*** METHODS OF THIS CLASS ***/
/*****************************/
/** This method allows you to directly select the 7 segments by choosing which LEDs to light. 
 *  limits the number of lines in the write_7seg() fun
 *      @param -- a, b, c, d, e, f, g -- the value '1' or '0' to be assigned to each segment
 *      no @return
 */
void Display4dig7seg::set_7seg(int a, int b, int c, int d, int e, int f, int g){
      digitalWrite(_seg_a, a);   
      digitalWrite(_seg_b, b);   
      digitalWrite(_seg_c, c);   
      digitalWrite(_seg_d, d);   
      digitalWrite(_seg_e, e);   
      digitalWrite(_seg_f, f);   
      digitalWrite(_seg_g, g); 
}

/**Allows direct selection of a number to be written on a dial with pre-configured digits.  
 *      @param -- value -- digit from 0 to 9 to be displayed. If not, display off (if -1, overflow)
 *      no @return 
 */
void Display4dig7seg::write_7seg(int value){
  switch(value){
    case 0 : 
      set_7seg(1,1,1,1,1,1,0);
      delay(1); 
      break;  

    case 1 : 
      set_7seg(0,1,1,0,0,0,0);
      delay(1); 
      break;  

    case 2 : 
      set_7seg(1,1,0,1,1,0,1);
      delay(1); 
      break;  

    case 3 : 
      set_7seg(1,1,1,1,0,0,1);
      delay(1); 
      break;  

    case 4 : 
      set_7seg(0,1,1,0,0,1,1);
      delay(1); 
      break;   

    case 5 : 
      set_7seg(1,0,1,1,0,1,1);
      delay(1); 
      break;  

    case 6 : 
      set_7seg(1,0,1,1,1,1,1);
      delay(1); 
      break;  

    case 7 : 
      set_7seg(1,1,1,0,0,0,0); 
      delay(1); 
      break;  

    case 8 : 
      set_7seg(1,1,1,1,1,1,1); 
      delay(1); 
      break;  

    case 9 : 
      set_7seg(1,1,1,0,0,1,1);
      delay(1); 
      break; 
    
    case -1 : 
      set_7seg(0,0,1,1,0,0,0);
      delay(1);

    default : 
      set_7seg(0,0,0,0,0,0,0);
      delay(1); 
      break;  
  }
}

/** This method allows you to select the right dial to light, using the logic '1' = ON and '0' = OFF.
 *      @param --dg1, dg2, dg3, dg4 -- the boulean value to be assigned to each dial, from 0 to 4 respectively
 */
void Display4dig7seg::set_digit(bool dg1, bool dg2, bool dg3, bool dg4){
    digitalWrite(_dgt_1, !dg1);
    digitalWrite(_dgt_2, !dg2);
    digitalWrite(_dgt_3, !dg3);
    digitalWrite(_dgt_4, !dg4);
}

/** This method is the shortcut function to be used to manipulate the 4-dial display. 
 *  Depending on the number of dials entered, the netoie method is used directly to avoid lighting up dials unnecessarily.
 *      @param -- value -- the number between 9999 and 0 tp be displayer
 *      no @return 
 */
void Display4dig7seg::print_4digit(int value){  
  int dgt1, dgt2, dgt3, dgt4;
  int printer = value;
  if(value > 9999)    
    set_digit(1,1,1,1);
    write_7seg(-1);

  // DIGIT 1 
  if(value > 999){
    dgt1 = int(value/1000); 
    value = value - dgt1*1000;
  }
  else 
    dgt1 = 10;
  
  set_digit(1,0,0,0);
  write_7seg(dgt1);

  // DIGIT 2 
  if((value < 999 && value > 99)){
    dgt2 = int(value/100); 
    value = value - dgt2*100;
  }
  else if(printer < 999)
    dgt2 = 0; 
  else 
    dgt2 = 10;
  
  set_digit(0,1,0,0);
  write_7seg(dgt2);
  

  // DIGIT 3 
  if(value < 99 && value > 9){
    dgt3 = int(value/10); 
    value = value - dgt3*10; 
  }
  else if(printer > 9)
    dgt3 = 0;
  else 
    dgt3 = 10; 
  set_digit(0,0,1,0);
  write_7seg(dgt3);


  // DIGIT 4
  if(value <= 9 && value > 0){
    dgt4 = int(value); 
    value = value - dgt4;
  }
  else 
    dgt4 = 0;
  set_digit(0,0,0,1);
  write_7seg(dgt4); 

}