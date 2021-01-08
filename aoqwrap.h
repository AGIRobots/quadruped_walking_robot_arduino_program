/*
Program Description
1. This program was created for use with the early quadruped robots made by AGIRobots.
2. Board used: arduino nano v3
　　You have to use ATmegs328p (Old Bootloader). 
    However, this does not apply if you have changed to the latest nano.
3. Other modules installed
　　　　74HC4067 x 2 : Multiplexer (used to add analog pins)
　　　　MPU6050 x 2 : Gyro sensor & temperature sensor
　　　　PCA9685 x 1 : Used to control RC servos
4. Specifications of the control board to be used (Available pins)
   Analog pins: A0~A3, Y0~Y15(A6), Y0~Y15(A7), total 36 pins
               *A4 (SDA) and A5 (SCL) are used for I2C communication.
               *A6 and A7 are input/output through multiplexer
                 → Specify the pins with multiplexer and execute analogRead(A6) and analogRead(A7) to read them.
   Digital pins: D0~D3, D8~D13, total 10 pins
   　　　　　　　Four pins (D4~D7) are used to control the multiplexer.
5. Functions available in this library (Available through AOQWRobotController class)
    void servoWrite(int ser_n, int deg);            //Function to rotate a servo
    int servoGetDeg(int analog_val, serType type);  //Function to get the rotation angle from a modified PWM servo.
    int setMultiPin(int pin_num);                   //Function to specify the multiplexer pins.
    void BoardInit();                               //Initializer
*/

#ifndef _aoqwrap_h
#define _aoqwrap_h
#include <arduino.h>


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/*Pulse width for general servo motor use*/
#define SERVOMIN 140
#define SERVOMAX 610
#define CENTER 375
/*
Define the input values at 0 degrees and 180 degrees 
that are needed to get the angle of a typical servo.
*/
/*Analog input at 0 degree (obtained from experiment) <- Be resourceful.*/
#define minVal 50   
/*Analog input at 180 degree (obtained from experiment) <- Be resourceful.*/
#define maxVal 600  

/*
In general, the pulse widths are as shown above, but the following 
pulse widths are most suitable for our servo (DS3218MG).
*/
#define DS3218MG_SERVOMIN 135
#define DS3218MG_SERVOMAX 615
#define DS3218MG_CENTER 375
/*
To get the angle of the servo used in this project (DS3218MG),
define the input value ranges of "0" and "180 degrees".
*/
/*Analog input at 0 degree (obtained from experiment) <- Be resourceful.*/
#define DS3218MG_minVal 55   
/*Analog input at 180 degree (obtained from experiment) <- Be resourceful.*/
#define DS3218MG_maxVal 610  

/*
An enumeration that allows you to simply specify the servos 
to be used by name and the appropriate parameters will be used.
*/
typedef enum {
    SG90,
    DS3218MG
} serType;

class AOQWRobotController
{
  public:
    //Function to rotate a servo
    void servoWrite(int ser_n, int deg, serType type);
    //Function to get the rotation angle from a modified PWM servo.
    int servoGetDeg(int analog_val, serType type);
    //Function to specify the multiplexer pins.
    int setMultiPin(int pin_num);
    //Initializer
    void BoardInit();
}; 
#endif
