/*
プログラムの説明
１．当プログラムは”春の企画　犬型ロボットの製作”で作成した制御基板用である。
２．使用ボード：arduino nano v3
　　ATmegs328p(Old Bootloader)を使用しなければならない。ただし、最新のnanoに変更した場合はその限りでない。
３．その他、搭載モジュール
　　　　74HC4067 × 2 : マルチプレクサ（アナログピンの増設に使用）
　　　　MPU6050 × 2 : ジャイロセンサ＆温度センサ
　　　　PCA9685 × 1 : RCサーボの制御に使用
４．当ボードの最終的スペック　(使用可能なピン)
   アナログピン：A0~A3, Y0~Y15(A6), Y0~Y15(A7) の計36本
               ※A4(SDA)とA5(SCL)は、I2C通信で使用している。
               ※A6及びA7はマルチプレクサを通じて入出力をする→マルチプレクサでピンを指定しanalogRead(A6)およびanalogRead(A7)を実行することで読み取れる。
   デジタルピン：D0~D3, D8~D13 の計10本
   　　　　　　　※D4~D7の4本はマルチプレクサを制御するために使用している。
５．定義した関数について
   servoWrite(int ser_n, int deg)          : PCA9685に一般的なサーボを接続したときにサーボを回転させるときに使用
   servo_get_deg(int analog_val)           : 一般的なサーボのポテンショメータの取得したアナログ値から角度へ変換
   DS3218MG_servoWrite(int ser_n, int deg)   : PCA9685にDS3218MGを接続したときにサーボを回転させるときに使用
   DS3218MG_servo_get_deg(int analog_val)    : DS3218MGのポテンショメータの取得したアナログ値から角度へ変換
   set_multi_pin(int pin_num)              : マルチプレクサ(multiplexer)のピンを指定する
*/

//サーボ制御に関するスケッチ(始)==========================================================================================================================================================================================
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//一般的なサーボの場合
#define SERVOMIN 140
#define SERVOMAX 610
#define CENTER 375
//一般的なサーボの角度を取得するために0度のときと180度のときの入力値幅を定義する。
#define minVal 50   //0度の時のアナログ入力(実験から得られた)                       <---------------------------------------------------(臨機応変に変更すること)
#define maxVal 600   //180度の時のアナログ入力(実験から得られた)                    <---------------------------------------------------(臨機応変に変更すること)

//一般的には上記のパルス幅のようだが、今回使用するサーボ(DS3218MG)は以下のパルス幅が最も合致した。
#define DS3218MG_SERVOMIN 135
#define DS3218MG_SERVOMAX 615
#define DS3218MG_CENTER 375    //CENTERと同じ
//今回使用するサーボ(DS3218MG)の角度を取得するために0度のときと180度のときの入力値幅を定義する。
#define DS3218MG_minVal 55   //0度の時のアナログ入力(実験から得られた)
#define DS3218MG_maxVal 610   //180度の時のアナログ入力(実験から得られた)

//一般的なサーボ(SG90など)を接続時
//サーボを動かす
int servoWrite(int ser_n, int deg) {
  deg = map(deg, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(ser_n, 0, deg);
}
//アナログ値から角度へ変換
int servo_get_deg(int analog_val) {
  int deg = map(analog_val, minVal, maxVal, 0, 180);
  return deg;
}

//DS3218MG使用時
//サーボを動かす
int DS3218MG_servoWrite(int ser_n, int deg) {
  deg = map(deg, 0, 180, DS3218MG_SERVOMIN, DS3218MG_SERVOMAX);
  pwm.setPWM(ser_n, 0, deg);
}
//アナログ値から角度へ変換
int DS3218MG_servo_get_deg(int analog_val) {
  int deg = map(analog_val, DS3218MG_minVal, DS3218MG_maxVal, 0, 180);
  return deg;
}

//サーボ制御に関するスケッチ(終)==========================================================================================================================================================================================
//マルチプレクサによるアナログピン増設に関するスケッチ(始)====================================================================================================================================================================
//マルチプレクサ(multiplexer)のピンを指定する関数
int set_multi_pin(int pin_num) {  
  //マルチプレクサのピン(Y0~Y15)のうち、対象の部分をセットする関数。
  //pin_numではY0~Y15を0~15で指定。
  
  //アセンブリ言語を使用して高速化を行うため、簡単に説明する。
  //ATmega328pの入出力ピンは、D0~D7がPORTD(PD)で管理される。(D8~D13はPORTB、A0~A5はPORTC)
  //D0からD7は二進数で定義でき、PORTD = 0b00000000としたら、D0~D7はすべてLOW ※0bD7D6D5D4D3D2D1D0の順。
  //１．0のピンは変更なし、1のピンのみLOWにしたければ、PORTD &= ~0bD7D6D5D4D3D2D1D0; //D7D6D5D4D3D2D1D0は任意
  //２．0のピンは変更なし、1のピンのみHIGHにしたければ、PORTD |= 0bD7D6D5D4D3D2D1D0; //D7D6D5D4D3D2D1D0は任意
  //その他にも様々な方法があるが、今回使用するのは上の2つ。共通するのは、1に指定したピン以外には変更を加えないということで、それはマルチプレクサの制御に使用するのが、D4~D7のみであることに起因する。

  //以下では2ステップでD4~D7を指定する。
  //①D4~D7を全て0で初期化する
  //➁D4~D7のうち、対応ピンのみ1にする
  
  PORTD &= ~0b11110000;    //①     
  switch (pin_num) {       //➁
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
//マルチプレクサによるアナログピン増設に関するスケッチ(終)====================================================================================================================================================================

void setup() {
  //74HC4067のピンを決定するために使用
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  //サーボを制御するために使用
  pwm.begin();
  pwm.setPWMFreq(60);

  Serial.begin(115200);
  
  //実験に必要 
  set_multi_pin(0);
}


/*サーボの接続ピンと名前*/
//頭のサーボ系
#define left_head_servo 0
#define right_head_servo 1
#define center_head_servo 2
//左前腕のサーボ系
#define forward_left_arm_1 4
#define forward_left_arm_2 5
#define forward_left_shoulder 6
//右前腕のサーボ系
#define forward_right_arm_1 9
#define forward_right_arm_2 8
#define forward_right_shoulder 7
//左後腕のサーボ系
#define back_left_arm_1 10
#define back_left_arm_2 11
#define back_left_shoulder 12
//右後腕のサーボ系
#define back_right_arm_1 15
#define back_right_arm_2 14
#define back_right_shoulder 13

void loop() {
  delay(1000);
  int deg1 = 110;
  int deg2 = 10;
  int deg3 = 0;
  
  DS3218MG_servoWrite(forward_left_shoulder,deg1);
  //DS3218MG_servoWrite(forward_right_shoulder,180-deg1);
  DS3218MG_servoWrite(forward_left_arm_2,deg2);
  //DS3218MG_servoWrite(forward_right_arm_2,180-deg2);
  DS3218MG_servoWrite(forward_left_arm_1,deg3);
  //DS3218MG_servoWrite(forward_right_arm_1,180-deg3);
  /*
  DS3218MG_servoWrite(back_left_shoulder,deg1);
  DS3218MG_servoWrite(back_right_shoulder,180-deg1);
  DS3218MG_servoWrite(back_left_arm_2,deg2);
  DS3218MG_servoWrite(back_right_arm_2,180-deg2);
  DS3218MG_servoWrite(back_left_arm_1,deg3);
  DS3218MG_servoWrite(back_right_arm_1,180-deg3);
  */
  delay(1000);
  deg1 = 90;
  deg2 = 90;
  deg3 = 100;
  DS3218MG_servoWrite(forward_left_shoulder,deg1);
  //DS3218MG_servoWrite(forward_right_shoulder,180-deg1);
  DS3218MG_servoWrite(forward_left_arm_2,deg2);
  //DS3218MG_servoWrite(forward_right_arm_2,180-deg2);
  DS3218MG_servoWrite(forward_left_arm_1,deg3);
  //DS3218MG_servoWrite(forward_right_arm_1,180-deg3);
  /*
  DS3218MG_servoWrite(back_left_shoulder,deg1);
  DS3218MG_servoWrite(back_right_shoulder,180-deg1);
  DS3218MG_servoWrite(back_left_arm_2,deg2);
  DS3218MG_servoWrite(back_right_arm_2,180-deg2);
  DS3218MG_servoWrite(back_left_arm_1,deg3);
  DS3218MG_servoWrite(back_right_arm_1,180-deg3);
  */
  /*
  for (int deg=0; deg < 180; deg++) {
    DS3218MG_servoWrite(0, deg);
    Serial.println(DS3218MG_servo_get_deg(analogRead(6)));
    delay(10); 
  }
  for (int deg=0; deg < 180; deg++) {
    DS3218MG_servoWrite(0, 180-deg);
    Serial.println(DS3218MG_servo_get_deg(analogRead(6)));
    delay(50); 
  }*/
  
  /*
  set_multi_pin(0); int num = analogRead(A6); Serial.println(num);
  int deg = map(num, 0, 1023, 0, 180);
  servoWrite(0, deg); servoWrite(1, 180-deg);
  */
  /*
  //外界の力に応じて、角度を取得しながら脱力せずに動かす。
  set_multi_pin(0); int num = analogRead(A6); int deg = DS3218MG_servo_get_deg(num);
  Serial.println(deg);
  DS3218MG_servoWrite(0, deg);
  */
  /*
  float deg_diff;
  
  int target = 145;
  do {
     set_multi_pin(0); int num = analogRead(A6); int deg = DS3218MG_servo_get_deg(num);  
     deg_diff = target - deg;
     DS3218MG_servoWrite(0, deg + deg_diff / exp(abs(deg_diff) / 40));
     Serial.println(deg);
  }while(abs(deg_diff) > 4); 
  
  target = 0;
  do {
     set_multi_pin(0); int num = analogRead(A6); int deg = DS3218MG_servo_get_deg(num);  
     deg_diff = target - deg;
     DS3218MG_servoWrite(0, deg + deg_diff / exp(abs(deg_diff) / 40));
     Serial.println(deg);
  }while(abs(deg_diff) > 4);*/
}


/*サンプル
int num[2][16];

void loop() {
  for (int i=0; i<16; i++) {
    set_multi_pin(i);     //マルチプレクサ上のピンを指定する
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

int get_all_servo_degree(int *all_servo_degree[16]) {
  //A6に接続された74hc4067に接続された16個全てのサーボの角度を取得する関数。
  //リストで16個のサーボの角度を取得するため、リストのポインタをリストとして与える。
  int val;
  
  for (int i=0; i<16; i++) {
    set_multi_pin(i);
    val = analogRead(A6);
    *all_servo_degree[i] = DS3218MG_servo_get_deg(val);
  }
}
