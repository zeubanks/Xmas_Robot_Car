
#include <Servo.h>
#define trigPin 5
#define echoPin 4
#define motorpin 2

//define LED pins
int blueled=26;
int redled=24;
int greenled=22;

long duration, distance;
int d1; //dist<50?
int d2; //dist<25?
int dist; //may take values 0, 1, or 2 depending on sensor distance
int lastdist;  //remembers the previous dist value

int countA; //counter for driving loops
int dir;  //alternates 1 and -1 to switch turn direction from left to right


// Define steering servo
Servo servo1;

// Angle setpoints for steering servo
int servo1Neutral = 40;
int servo1Right = 80; 
int servo1Left = 0;

void setup() {
Serial.begin (9600);

//set initial variable values
countA=0; 
dir=1;
dist=0;
lastdist=0;
 
// Attach servo
servo1.attach(3);

// Set servo to Neutral position
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
//set d1 and d2 back to 0
d1=0;
d2=0;

checkdist(); //run checkdist

//dist=0 when distance>50
//turn on green LED, drive straight in faster speed
if (dist==0){
    digitalWrite(greenled,HIGH); 
    digitalWrite(blueled,LOW);
    digitalWrite(redled,LOW);
    wheelstraight();
    fwf1();
  }

//dist=1 when 50>distance>25 
//turn on blue LED, turn left or right and go slower speed
if (dist==1){
  
    if (dist!=lastdist){
    dir=-1*dir;  //change turn direction for each obstacle
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

//dist=2 when distance<25 
//turn on red LED, turn wheel to neutral, and stop for human realignment
if (dist==2){
    digitalWrite(greenled,LOW);
    digitalWrite(blueled,LOW);
    digitalWrite(redled,HIGH);
    wheelstraight();
    digitalWrite(motorpin,LOW);
  }
}

//determine distance to obstruction
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
  
//turn wheel to neutral position
void wheelstraight(){
  servo1.write(servo1Neutral);
 }

//turn wheel to right position
void wheelright(){
  servo1.write(servo1Right);
 }

//turn wheel to left position
void wheelleft(){
  servo1.write(servo1Left);
 }

//drive slowly for 1 second
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


//drive fast for 1 second
  void fwf1(){
  countA=0;
  while(countA < 100){
  digitalWrite(motorpin,HIGH);
  delay(10);
  countA=countA + 1;
 }
 }

