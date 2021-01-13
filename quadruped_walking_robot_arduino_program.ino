#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "aoqwrap.h"

AOQWRobotController RC;

typedef enum {
  FLEFT, /*front left*/
  FRIGHT, /*front right*/
  BLEFT, /*back left*/ 
  BRIGHT /*back right*/
} legPosition;

void setup() {
  RC.BoardInit();

  Serial.begin(115200);
  
  //実験に必要 
  RC.setMultiPin(0);
  // delay(10000);
}


/*Part name of the servo connected to PCA9685*/
//head
#define left_head_servo 0
#define right_head_servo 1
#define center_head_servo 2
//front leg (left)
#define front_leg_left_1 5
#define front_leg_left_2 4
#define front_left_shoulder 8
//front leg (right)
#define front_leg_right_1 6
#define front_leg_right_2 7
#define front_right_shoulder 9 
//back leg (left)
#define back_leg_left_1 14
#define back_leg_left_2 12
#define back_left_shoulder 10
//back leg (right)
#define back_leg_right_1 15
#define back_leg_right_2 13
#define back_right_shoulder 11

void bendingAndStretching(legPosition lp) {
  switch (lp) {
    case FLEFT:
      RC.servoWrite(front_leg_left_2, 180-180, DS3218MG);
      RC.servoWrite(front_left_shoulder, 180-30, DS3218MG);
      delay(150);
      RC.servoWrite(front_leg_left_2, 180-120, DS3218MG);
      RC.servoWrite(front_left_shoulder, 180-80, DS3218MG);
      delay(150);
      break;
    case FRIGHT:
      RC.servoWrite(front_leg_right_2, 180, DS3218MG);
      RC.servoWrite(front_right_shoulder, 30, DS3218MG);
      delay(150);
      RC.servoWrite(front_leg_right_2, 120, DS3218MG);
      RC.servoWrite(front_right_shoulder, 80, DS3218MG);
      delay(150);
      break;
    case BLEFT:
      RC.servoWrite(back_leg_left_2, 180-180, DS3218MG);
      RC.servoWrite(back_left_shoulder, 180-30, DS3218MG);
      delay(150);
      RC.servoWrite(back_leg_left_2, 180-120, DS3218MG);
      RC.servoWrite(back_left_shoulder, 180-70, DS3218MG);
      delay(150);
      break;
    case BRIGHT:
      RC.servoWrite(back_leg_right_2, 180, DS3218MG);
      RC.servoWrite(back_right_shoulder, 30, DS3218MG);
      delay(150);
      RC.servoWrite(back_leg_right_2, 120, DS3218MG);
      RC.servoWrite(back_right_shoulder, 70, DS3218MG);
      delay(150);
      break;
    default:
      break;
  }
}

void flRigth(int posNum, int st, int mt, int et){
  switch (posNum) {
    case 1:
      RC.servoWrite(front_leg_right_1, 150, DS3218MG); RC.servoWrite(front_leg_right_2, 180, DS3218MG); RC.servoWrite(front_right_shoulder, st, DS3218MG);
      break;
    case 2:
      RC.servoWrite(front_leg_right_1, 150, DS3218MG); RC.servoWrite(front_leg_right_2, 180, DS3218MG); RC.servoWrite(front_right_shoulder, mt, DS3218MG); 
      break;
    case 3:
      RC.servoWrite(front_leg_right_1, 150, DS3218MG); RC.servoWrite(front_leg_right_2, 150, DS3218MG); RC.servoWrite(front_right_shoulder, mt, DS3218MG); 
      break;
    case 4:
      RC.servoWrite(front_leg_right_1, 150, DS3218MG); RC.servoWrite(front_leg_right_2, 150, DS3218MG); RC.servoWrite(front_right_shoulder, et, DS3218MG); 
      break;
    default:
      break;;
  }
}

void blRight(int posNum, int st, int mt, int et){
  switch (posNum) {
    case 1:
      RC.servoWrite(back_leg_right_1, 150, DS3218MG); RC.servoWrite(back_leg_right_2, 180, DS3218MG); RC.servoWrite(back_right_shoulder, st, DS3218MG);
      break;
    case 2:
      RC.servoWrite(back_leg_right_1, 150, DS3218MG); RC.servoWrite(back_leg_right_2, 180, DS3218MG); RC.servoWrite(back_right_shoulder, mt, DS3218MG); 
      break;
    case 3:
      RC.servoWrite(back_leg_right_1, 150, DS3218MG); RC.servoWrite(back_leg_right_2, 150, DS3218MG); RC.servoWrite(back_right_shoulder, mt, DS3218MG); 
      break;
    case 4:
      RC.servoWrite(back_leg_right_1, 150, DS3218MG); RC.servoWrite(back_leg_right_2, 150, DS3218MG); RC.servoWrite(back_right_shoulder, et, DS3218MG); 
      break;
    default:
      break;;
  }
}

void flLeft(int posNum, int st, int mt, int et){
  switch (posNum) {
    case 1:
      RC.servoWrite(front_leg_left_1, 180-150, DS3218MG); RC.servoWrite(front_leg_left_2, 180-180, DS3218MG); RC.servoWrite(front_left_shoulder, 180-st, DS3218MG);
      break;
    case 2:
      RC.servoWrite(front_leg_left_1, 180-150, DS3218MG); RC.servoWrite(front_leg_left_2, 180-180, DS3218MG); RC.servoWrite(front_left_shoulder, 180-mt, DS3218MG); 
      break;
    case 3:
      RC.servoWrite(front_leg_left_1, 180-150, DS3218MG); RC.servoWrite(front_leg_left_2, 180-150, DS3218MG); RC.servoWrite(front_left_shoulder, 180-mt, DS3218MG); 
      break;
    case 4:
      RC.servoWrite(front_leg_left_1, 180-150, DS3218MG); RC.servoWrite(front_leg_left_2, 180-150, DS3218MG); RC.servoWrite(front_left_shoulder, 180-et, DS3218MG); 
      break;
    default:
      break;;
  }
}

void blLeft(int posNum, int st, int mt, int et){
  switch (posNum) {
    case 1:
      RC.servoWrite(back_leg_left_1, 180-150, DS3218MG); RC.servoWrite(back_leg_left_2, 180-180, DS3218MG); RC.servoWrite(back_left_shoulder, 180-st, DS3218MG);
      break;
    case 2:
      RC.servoWrite(back_leg_left_1, 180-150, DS3218MG); RC.servoWrite(back_leg_left_2, 180-180, DS3218MG); RC.servoWrite(back_left_shoulder, 180-mt, DS3218MG);
      break; 
    case 3:
      RC.servoWrite(back_leg_left_1, 180-150, DS3218MG); RC.servoWrite(back_leg_left_2, 180-150, DS3218MG); RC.servoWrite(back_left_shoulder, 180-mt, DS3218MG);
      break; 
    case 4:
      RC.servoWrite(back_leg_left_1, 180-150, DS3218MG); RC.servoWrite(back_leg_left_2, 180-150, DS3218MG); RC.servoWrite(back_left_shoulder, 180-et, DS3218MG);
      break; 
    default:
      break;
  }
}



void loop() {
  // bendingAndStretching(FLEFT);
  // bendingAndStretching(FRIGHT);
  // bendingAndStretching(BLEFT);
  // bendingAndStretching(BRIGHT);
 
  // RC.servoWrite(front_leg_right_1, 0, EXHAUSTION);
  // RC.servoWrite(center_head_servo, 160, SG90);
  // RC.servoWrite(left_head_servo, 130, SG90);
  // RC.servoWrite(right_head_servo,130, SG90);

  // RC.servoWrite(front_leg_right_1, 0, EXHAUSTION);
  // RC.servoWrite(front_leg_right_2, 0, EXHAUSTION);
  // RC.servoWrite(front_right_shoulder, 0, EXHAUSTION);
  // RC.servoWrite(front_leg_left_1, 0, EXHAUSTION);
  // RC.servoWrite(front_leg_left_2, 0, EXHAUSTION);
  // RC.servoWrite(front_left_shoulder, 0, EXHAUSTION);
  // RC.servoWrite(back_leg_right_1, 0, EXHAUSTION);
  // RC.servoWrite(back_leg_right_2, 0, EXHAUSTION);
  // RC.servoWrite(back_right_shoulder, 0, EXHAUSTION);
  // RC.servoWrite(back_leg_left_1, 0, EXHAUSTION);
  // RC.servoWrite(back_leg_left_2, 0, EXHAUSTION);
  // RC.servoWrite(back_left_shoulder, 0, EXHAUSTION);

  // RC.setMultiPin(15); int num_s = analogRead(A7); int deg_s = RC.servoGetDeg(num_s, DS3218MG); Serial.print(deg_s); Serial.print(":");
  // RC.setMultiPin(14); num_s = analogRead(A7); deg_s = RC.servoGetDeg(num_s, DS3218MG); Serial.print(deg_s); Serial.print(":");
  // RC.setMultiPin(13); num_s = analogRead(A7); deg_s = RC.servoGetDeg(num_s, DS3218MG); Serial.println(deg_s);
  int arg1 = 90
  flRigth(1, arg1, 90, 35); blLeft(1, arg1, 80, 25); flLeft(3, arg1, 90, 35); blRight(3, arg1, 80, 25); delay(200);
  flRigth(2, arg1, 90, 35); blLeft(2, arg1, 80, 25); flLeft(4, arg1, 90, 35); blRight(4, arg1, 80, 25); delay(200);
  flRigth(3, arg1, 90, 35); blLeft(3, arg1, 80, 25); flLeft(1, arg1, 90, 35); blRight(1, arg1, 80, 25); delay(200);
  flRigth(4, arg1, 90, 35); blLeft(4, arg1, 80, 25); flLeft(2, arg1, 90, 35); blRight(2, arg1, 80, 25); delay(200);
}
  // delay(1000);
  // RC.servoWrite(front_leg_right_1, 0, EXHAUSTION);
  // RC.servoWrite(left_head_servo, 0, EXHAUSTION);
  // RC.servoWrite(right_head_servo, 0, EXHAUSTION);
  // RC.servoWrite(center_head_servo, 0, EXHAUSTION);
  // RC.servoWrite(center_head_servo, 160, SG90);
  // RC.servoWrite(left_head_servo, 50, SG90);
  // RC.servoWrite(right_head_servo,50, SG90);
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
