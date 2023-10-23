

/*void setup(){
  GreenBeacon beacon = GreenBeacon("017190a280");
  beacon.start("Hello");
}

void loop(){
  double n;
  if(n < ){

  }
  else{

  }
}*/


//LEDの足が短い方がマイナス、GNDはマイナスにつなぐ
//抵抗は長い方につける
#include "GreenBeacon.h"
#define echoPin 18 // Echo Pin yellow
#define trigPin 5 // Trigger Pin green
 
double Duration = 0; //受信した間隔
double Distance = 0; //距離

String hwid = 017190a280;

int led1 = 19; //LEDがついている位置
 
void setup() {
Serial.begin( 115200 );//Arduino Unoは9600,ESPで試す場合はは115200
pinMode( echoPin, INPUT );
pinMode( trigPin, OUTPUT );
pinMode(led1,OUTPUT);
}
 
void loop() {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite( trigPin, HIGH ); //超音波を出力
  delayMicroseconds( 10 ); //
  digitalWrite( trigPin, LOW );
  
  Duration = pulseIn( echoPin, HIGH ); //センサからの入力
  if (Duration > 0) {
    Duration = Duration/2; //往復距離を半分にする
    Distance = Duration*340*100/1000000; // 音速を340m/sに設定
    Serial.print("Distance:");
    Serial.print(Distance);
    Serial.println(" cm");

    if (Distance < 20) {        //  20cm以内になるとLED1が点灯
      digitalWrite(led1, HIGH);
      delay(1000); //取得間隔1秒
      digitalWrite(led1, LOW);
      GreenBeacon beacon = GreenBeacon(hwid);
      beacon.start("Hello");
    }
    else{
      Serial.println("距離外");
    }
  }

  
  

}