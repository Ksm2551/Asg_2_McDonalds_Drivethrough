#include<Servo.h>
#define echoPin1 1
#define trigPin1 0
#define echoPin2 3
#define trigPin2 2
Servo servo_1;
Servo servo_2;
int flag=0;
int pos1=90;
int pos2=90;
int led_r=8;
int led_b=9;
int led_g=12;
int led_y=13;
int ir_1=4;
int ir_2=5;
int ir_3=6;
int ir_4=7;
int pin1=HIGH;
int pin2=HIGH;
int pin3=HIGH;
int pin4=HIGH;
long duration1, distance1, duration2, distance2;
void setup() {
Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led_r, OUTPUT);
  pinMode(led_b, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(led_y, OUTPUT);
  pinMode(ir_1, INPUT);
  pinMode(ir_2, INPUT);
  pinMode(ir_3, INPUT);
  pinMode(ir_4, INPUT);
  servo_1.attach(10);
  servo_2.attach(11);
}
void loop() {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(100);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin1, LOW);
  distance1=duration1/52.8;
  if(distance1<=0.3){
    for(pos1=0; pos1<=90;pos1+=1){
      servo_1.write(pos1); //writing the angle of movement in deg
      delay(15); //delay of 15 ms
    }
    Serial.println(F("Barricades open"));
    delay(5000);
    for(pos1=90;pos1>=0;pos1-=1){
      servo_1.write(pos1);
      delay(15);
    }
    Serial.println(F("Barricades closed"));
    flag=1;
  }
  if(flag==1){
    pin1 = digitalRead(ir_1);
    pin2 = digitalRead(ir_2);
    pin3 = digitalRead(ir_3);
    pin4 = digitalRead(ir_4);
    delay(1000);
    if(pin1==HIGH){
      digitalWrite(led_r,HIGH);
      digitalWrite(led_b,LOW);
      digitalWrite(led_g,LOW);
      digitalWrite(led_y,LOW);
      Serial.println(F("Menu 1 Selected"));
    }
    else if(pin2==HIGH){
      digitalWrite(led_r,LOW);
      digitalWrite(led_b,HIGH);
      digitalWrite(led_g,LOW);
      digitalWrite(led_y,LOW);
      Serial.println(F("Menu 2 Selected"));
    }
    else if(pin3==HIGH){
      digitalWrite(led_r,LOW);
      digitalWrite(led_b,LOW);
      digitalWrite(led_g,HIGH);
      digitalWrite(led_y,LOW);
      Serial.println(F("Menu 3 Selected"));
    }
    else if(pin4==HIGH){
      digitalWrite(led_r,LOW);
      digitalWrite(led_b,LOW);
      digitalWrite(led_g,LOW);
      digitalWrite(led_y,HIGH);
      Serial.println(F("Menu 4 Selected"));
    }
    else if((pin1!=HIGH) && (pin2!=HIGH) && (pin3!=HIGH) && (pin4!=HIGH)){
      digitalWrite(led_r,LOW);
      digitalWrite(led_b,LOW);
      digitalWrite(led_g,LOW);
      digitalWrite(led_y,LOW);
    }
  	delay(5000);
    flag=2;
    if(flag==2){
      digitalWrite(trigPin2, LOW);
      delayMicroseconds(100);
      digitalWrite(trigPin2, HIGH);
      delayMicroseconds(100);
      digitalWrite(trigPin2, LOW);
      distance2=duration2/52.8;
      if(distance2<=0.3){
        for(pos2=0; pos2<=90;pos2+=1){
          servo_2.write(pos2); //writing the angle of movement in deg
          delay(15); //delay of 15 ms
        }
        Serial.println(F("Barricades open"));
        delay(5000);
        for(pos2=90;pos2>=0;pos2-=1){
          servo_2.write(pos2);
          delay(15);
        }
        Serial.println(F("Barricades closed"));
      }
    }
  }
}