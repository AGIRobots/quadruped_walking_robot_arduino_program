#include <arduino.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "aoqwrap.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Function to rotate a servo
void AOQWRobotController::servoWrite(int ser_n, int deg, serType type) {
  switch(type){
    case SG90:
      deg = map(deg, 0, 180, SERVOMIN, SERVOMAX);
      pwm.setPWM(ser_n, 0, deg);
      break;
    case DS3218MG:
      deg = map(deg, 0, 180, DS3218MG_SERVOMIN, DS3218MG_SERVOMAX);
      pwm.setPWM(ser_n, 0, deg);
      break;
    default:
      break;
  }  
}

//Function to get the rotation angle from a modified PWM servo.
int AOQWRobotController::servoGetDeg(int analog_val, serType type) {
  int deg;
  switch(type){
    case SG90:
      deg = map(analog_val, minVal, maxVal, 0, 180);
      return deg;
    case DS3218MG:
      deg = map(analog_val, DS3218MG_minVal, DS3218MG_maxVal, 0, 180);
      return deg;
    default:
      break;
  }
}

/*
(Function to specify the multiplexer pins.)
Function to set the appropriate pin among the multiplexer pins (Y0~Y15).
For pin_num, specify Y0~Y15 as 0~15.
Assembly language was used to speed up the process.
  *The input/output pins of ATmega328p, D0~D7 are managed by PORTD(PD). (D8~D13 is PORTB, A0~A5 is PORTC)
  *D0~D7 can be defined in binary, if PORTD = 0b00000000, then D0~D7 are all LOW. 
    *The order is 0bD7D6D5D4D3D2D1D0.
  *If you want to leave pin0 unchanged and only pin1 LOW, "PORTD &= ~0bD7D6D5D4D3D2D1D0; //D7D6D5D4D3D2D1D0 is optional".
  *If you want to leave pin0 unchanged and only pin1 HIGH, "PORTD |= 0bD7D6D5D4D3D2D1D0; //D7D6D5D4D3D2D1D0 is optional".
  *The common denominator is that no changes are made to pins other than the one specified as 1, 
   which is due to the fact that only D4~D7 are used to control the multiplexer.

  //In the following, D4~D7 are specified in two steps.
  //Location (a) Initialize all D4~D7 with 0
  //Location (b) Set only the corresponding pins of D4~D7 to 1
*/
int AOQWRobotController::setMultiPin(int pin_num) {  
  PORTD &= ~0b11110000;    //(a)
  switch (pin_num) {       //(b)
    case 0: //0000
      PORTD |= 0b00000000; break;
    case 1: //0000
      PORTD |= 0b10000000; break;
    case 2: //0000
      PORTD |= 0b01000000; break;
    case 3: //0000
      PORTD |= 0b11000000; break;
    case 4: //0000
      PORTD |= 0b00100000; break;
    case 5: //0000
      PORTD |= 0b10100000; break;
    case 6: //0000
      PORTD |= 0b01100000; break;
    case 7: //0000
      PORTD |= 0b11100000; break;
    case 8: //0000
      PORTD |= 0b00010000; break;
    case 9: //0000
      PORTD |= 0b10010000; break;
    case 10: //0000
      PORTD |= 0b01010000; break;
    case 11: //0000
      PORTD |= 0b11010000; break;
    case 12: //0000
      PORTD |= 0b00110000; break;
    case 13: //0000
      PORTD |= 0b10110000; break;
    case 14: //0000
      PORTD |= 0b01110000; break;
    case 15: //0000
      PORTD |= 0b11110000; break;
  }
  return 0;
}

//Initializer
void AOQWRobotController::BoardInit(){
  //Multiplexer control pins
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pwm.begin();
  pwm.setPWMFreq(60);
}
