//LEDの足が短い方がマイナス、GNDはマイナスにつなぐ
//抵抗は長い方につける
//右がスピーカーでスピーカーに筒をつける
//10cm単位で小数点以下四捨五入

#include "GreenBeacon.h"
#define echoPin 18 // Echo Pin yellow
#define trigPin 5 // Trigger Pin green
 
double Duration = 0; //受信した間隔
double Distance1 = 0; //距離
double Distance2 = 0;
double Distance3 = 0;
double Distance21 = 0;
double Distance23 = 0;
double Distance = 0;

int led1 = 19; //LEDがついている位置
 
void setup() {
  
  Serial.begin( 115200 );//Arduino Unoは9600,ESPで試す場合はは115200
  pinMode( echoPin, INPUT );
  pinMode( trigPin, OUTPUT );
  pinMode(led1,OUTPUT);

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite( trigPin, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin, LOW );
  
  Duration = pulseIn( echoPin, HIGH ); //センサからの入力
  if (Duration > 0) {
    Duration = Duration/2; //往復距離を半分にする
    Distance1 = (int)((Duration*340*100/1000000)/10)*10; // 音速を340m/sに設定
    Serial.print("Distance1 : ");
    Serial.print(Distance1);
    Serial.println(" cm");
  }
  delay(250);
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite( trigPin, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin, LOW );
  Duration = pulseIn( echoPin, HIGH ); //センサからの入力
  if (Duration > 0) {
    Duration = Duration/2; //往復距離を半分にする
    Distance2 = (int)((Duration*340*100/1000000)/10)*10; // 音速を340m/sに設定
    Serial.print("Distance2 : ");
    Serial.print(Distance2);
    Serial.println(" cm");
  }

  delay(250);
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite( trigPin, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin, LOW );
  Duration = pulseIn( echoPin, HIGH ); //センサからの入力
  if (Duration > 0) {
    Duration = Duration/2; //往復距離を半分にする
    Distance3 = (int)((Duration*340*100/1000000)/10)*10; // 音速を340m/sに設定
    Serial.print("Distance3 : ");
    Serial.print(Distance3);
    Serial.println(" cm");
  }

  Distance21 = Distance2 - Distance1;
  Distance23 = Distance2 - Distance3;
  if(Distance21 == 0 || Distance23 == 0){
    Distance = Distance2;
  }
  else if(Distance21 - Distance23 == 0){
    Distance = Distance1;
  }
  else if(Distance21 - Distance23 >= -30 && Distance21 - Distance23 <= 30){
    Distance = (Distance1 + Distance3) / 2;
  }
  else if((Distance21 >= -30 && Distance21 <= 30) || (Distance23 >= -30 && Distance23 <= 30)){
    Distance = Distance2;
  }

  if (Distance < 100) {        //  100cm以内になるとLED1が点灯
    digitalWrite(led1, HIGH);
    delay(500); //取得間隔0.5秒
    digitalWrite(led1, LOW);
    Serial.print("Distance  : ");
    Serial.print(Distance);
    Serial.println(" cm");
    GreenBeacon beacon = GreenBeacon("0171c239b0");
    beacon.start("Hello");
    delay(10000);
  }
  else{
    Serial.println("Distance  : 距離外");
  } 
  esp_sleep_enable_timer_wakeup(10000 * 1000);  // wakeup every 10.0secs
  esp_deep_sleep_start();
}
 
void loop() {
}