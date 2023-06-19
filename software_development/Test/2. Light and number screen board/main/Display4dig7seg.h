/* This library has been designed to control a 4-digit 7-segment display. It has been verified with a Luckylight display.
 * DISPLAY REFERENCE :  Luckylight L1309088
 * NUMBER OF PIN :      14 pins
 * COMPOSITION :        4 Display of 7 segment (+ segment dot) + digit for ":" print
 *
 * Created by Marion escouteloup, @maesc on Github
 * Last update : 13-06-2023 (DD-MM-YYYY)
 *        A
 *       ---
 *    F |   | B
 *      | G |
 *       ---
 *    E |   | C
 *      | D |
 *       ---
 */

#ifndef Display4dig7seg_h
#define Display4dig7seg_h

#include "Arduino.h"
#include <Wire.h>	

class Display4dig7seg{
  public : 
    // With dp and dot dot
    //Display4dig7seg(int seg_a, int seg_b, int seg_c, int seg_d,int seg_e, int seg_f, int seg_g, int seg_dp, int seg_dotdot, int dgt_1, int dgt_2, int dgt_3, int dgt_4, int dgt_dotdot); 
    
    // Without dp and dot dot
    Display4dig7seg(int seg_a, int seg_b, int seg_c, int seg_d, int seg_e, int seg_f, int seg_g, int dgt_1, int dgt_2, int dgt_3, int dgt_4); 
    
    void Display4dig7seg::set_7seg(int a, int b, int c, int d, int e, int f, int g);
    void Display4dig7seg::write_7seg(int value); 
    void Display4dig7seg::set_digit(bool dg1, bool dg2, bool dg3, bool dg4); 
    void Display4dig7seg::print_4digit(int value); 

  private : 
    int _seg_a;
    int _seg_b;
    int _seg_c;
    int _seg_d;
    int _seg_e;
    int _seg_f;
    int _seg_g;
    int _seg_dp; 
    int _seg_dotodt; 
    int _dgt_1;
    int _dgt_2;
    int _dgt_3;
    int _dgt_4;
    int _dgt_dotdot; 
};

#endif