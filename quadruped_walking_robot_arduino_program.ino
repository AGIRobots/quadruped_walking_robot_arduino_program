#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "aoqwrap.h"

AOQWRobotController RC;

void setup() {
  RC.BoardInit();

  Serial.begin(115200);
  
  //実験に必要 
  RC.setMultiPin(0);
  delay(10000);
}


/*Part name of the servo connected to PCA9685*/
//head
#define left_head_servo 0
#define right_head_servo 1
#define center_head_servo 2
//front leg (left)
#define front_leg_left_1 4
#define front_leg_left_2 5
#define front_left_shoulder 6
//front leg (right)
#define front_leg_right_1 9
#define front_leg_right_2 8
#define front_right_shoulder 7
//back leg (left)
#define back_leg_left_1 10
#define back_leg_left_2 11
#define back_left_shoulder 12
//back leg (right)
#define back_leg_right_1 15
#define back_leg_right_2 14
#define back_right_shoulder 13

void loop() {
  delay(1000);
  // int deg1 = 110;
  // int deg2 = 10;
  // int deg3 = 0;
  RC.servoWrite(center_head_servo, 160, SG90);
  RC.servoWrite(left_head_servo, 130, SG90);
  RC.servoWrite(right_head_servo,130, SG90);

  // DS3218MGservoWrite(front_left_shoulder,deg1);
  //DS3218MGservoWrite(front_right_shoulder,180-deg1);
  // DS3218MGservoWrite(front_leg_left_2,deg2);
  //DS3218MGservoWrite(front_leg_right_2,180-deg2);
  // DS3218MGservoWrite(front_leg_left_1,deg3);
  //DS3218MGservoWrite(front_leg_right_1,180-deg3);
  /*
  DS3218MGservoWrite(back_left_shoulder,deg1);
  DS3218MGservoWrite(back_right_shoulder,180-deg1);
  DS3218MGservoWrite(back_leg_left_2,deg2);
  DS3218MGservoWrite(back_leg_right_2,180-deg2);
  DS3218MGservoWrite(back_leg_left_1,deg3);
  DS3218MGservoWrite(back_leg_right_1,180-deg3);
  // */
  delay(1000);
  // deg1 = 90;
  // deg2 = 90;
  // deg3 = 100;
  RC.servoWrite(center_head_servo, 160, SG90);
  RC.servoWrite(left_head_servo, 50, SG90);
  RC.servoWrite(right_head_servo,50, SG90);
  // DS3218MGservoWrite(front_left_shoulder,deg1);
  //DS3218MGservoWrite(front_right_shoulder,180-deg1);
  // DS3218MGservoWrite(front_leg_left_2,deg2);
  //DS3218MGservoWrite(front_leg_right_2,180-deg2);
  // DS3218MGservoWrite(front_leg_left_1,deg3);
  //DS3218MGservoWrite(front_leg_right_1,180-deg3);
  /*
  DS3218MGservoWrite(back_left_shoulder,deg1);
  DS3218MGservoWrite(back_right_shoulder,180-deg1);
  DS3218MGservoWrite(back_leg_left_2,deg2);
  DS3218MGservoWrite(back_leg_right_2,180-deg2);
  DS3218MGservoWrite(back_leg_left_1,deg3);
  DS3218MGservoWrite(back_leg_right_1,180-deg3);
  */
  /*
  for (int deg=0; deg < 180; deg++) {
    DS3218MGservoWrite(0, deg);
    Serial.println(DS3218MGservoGetDeg(analogRead(6)));
    delay(10); 
  }
  for (int deg=0; deg < 180; deg++) {
    DS3218MGservoWrite(0, 180-deg);
    Serial.println(DS3218MGservoGetDeg(analogRead(6)));
    delay(50); 
  }*/
  
  /*
  setMultiPin(0); int num = analogRead(A6); Serial.println(num);
  int deg = map(num, 0, 1023, 0, 180);
  servoWrite(0, deg); servoWrite(1, 180-deg);
  */
  /*
  //外界の力に応じて、角度を取得しながら脱力せずに動かす。
  setMultiPin(0); int num = analogRead(A6); int deg = DS3218MGservoGetDeg(num);
  Serial.println(deg);
  DS3218MGservoWrite(0, deg);
  */
  /*
  float deg_diff;
  
  int target = 145;
  do {
     setMultiPin(0); int num = analogRead(A6); int deg = DS3218MGservoGetDeg(num);  
     deg_diff = target - deg;
     DS3218MGservoWrite(0, deg + deg_diff / exp(abs(deg_diff) / 40));
     Serial.println(deg);
  }while(abs(deg_diff) > 4); 
  
  target = 0;
  do {
     setMultiPin(0); int num = analogRead(A6); int deg = DS3218MGservoGetDeg(num);  
     deg_diff = target - deg;
     DS3218MGservoWrite(0, deg + deg_diff / exp(abs(deg_diff) / 40));
     Serial.println(deg);
  }while(abs(deg_diff) > 4);*/
}


/*サンプル
int num[2][16];

void loop() {
  for (int i=0; i<16; i++) {
    setMultiPin(i);     //マルチプレクサ上のピンを指定する
    num[0][i] = analogRead(A6); num[1][i] = analogRead(A7);    //ピンを指定した後は、analogRead()でA6, A7を指定すればよい。
  }
  
  //シリアルモニタへ表示
  for(int i=0; i<2; i++) {
    for(int j=0; j<16; j++){
      Serial.print(16 * i + j); Serial.print(" pin:");Serial.print(num[i][j]); Serial.print("  ");
    }
  }
  Serial.println();
}
*/

//int get_all_servo_degree(int *all_servo_degree[16]) {
//  //A6に接続された74hc4067に接続された16個全てのサーボの角度を取得する関数。setMultiPin
//  //リストで16個のサーボの角度を取得するため、リストのポインタをリストとして与える。
//  int val;
//  
//  for (int i=0; i<16; i++) {
//    setMultiPin(i);
//    val = analogRead(A6);
//    *all_servo_degree[i] = DS3218MGservoGetDeg(val);
//  }
//}
