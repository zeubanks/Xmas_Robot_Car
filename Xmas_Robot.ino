
#include <Servo.h>
#define trigPin 5
#define echoPin 4
#define motorpin 2

int blueled=26;
int redled=24;
int greenled=22;
int d1;
int d2;
int dist;
int countA;
long duration, distance;
int dir;
int lastdist;

  // Define steering servo
Servo servo1;

// Angle setpoints for servo1
int servo1Neutral = 40;
int servo1Right = 80; 
int servo1Left = 0;

void setup() {
countA=0;
dir=1;
dist=0;
lastdist=0;
Serial.begin (9600);
 
  // Attach all the servos
  servo1.attach(3);

  // Set all servos to Neutral
  servo1.write(servo1Neutral);

pinMode(motorpin,OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(blueled,OUTPUT);
pinMode(redled,OUTPUT);
pinMode(greenled,OUTPUT);
digitalWrite(motorpin,LOW);

}

void loop() {
  d1=0;
  d2=0;
checkdist();
  if (dist==0){
    digitalWrite(greenled,HIGH);
    digitalWrite(blueled,LOW);
    digitalWrite(redled,LOW);
  wheelstraight();
  fwf1();
  }
  
  if (dist==1){
     if (dist!=lastdist){
      dir=-1*dir;
     }
    digitalWrite(greenled,LOW);
    digitalWrite(blueled,HIGH);
    digitalWrite(redled,LOW);
    if (dir==1){
      wheelright();
    } else {
      wheelleft();
    }
    fwsl1();
  }
  
  if (dist==2){
    digitalWrite(greenled,LOW);
    digitalWrite(blueled,LOW);
    digitalWrite(redled,HIGH);
    wheelstraight();
    digitalWrite(motorpin,LOW);
  }

  
}

void checkdist(){
   digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance<50){
    d1=1;
  }
  if (distance < 25){
    d2=1;
  }
  lastdist=dist;
  dist=d1+d2;
  }
  

void wheelstraight(){
  servo1.write(servo1Neutral);
 }

void wheelright(){
  servo1.write(servo1Right);
 }

void wheelleft(){
  servo1.write(servo1Left);
 }

 void fwsl1(){
  countA=0;
  while(countA < 100){
  digitalWrite(motorpin,HIGH);
  delay(8);
  digitalWrite(motorpin,LOW);
  delay(2);
  countA=countA + 1;
 }
 }

  void fwf1(){
  countA=0;
  while(countA < 100){
  digitalWrite(motorpin,HIGH);
  delay(10);
  countA=countA + 1;
 }
 }

