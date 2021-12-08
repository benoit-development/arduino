#include <Servo.h>
#include "SR04.h"
Servo myservo;



#define SERVO_PIN 4

#define TRIG_PIN 3
#define ECHO_PIN 2

#define DIRA_1 6
#define DIRA_2 7

#define DIRB_1 8
#define DIRB_2 9

bool started = false;

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
 
void setup() {

  pinMode(DIRA_2,OUTPUT);
  pinMode(DIRB_2,OUTPUT);
  
  pinMode(DIRA_1,OUTPUT);
  pinMode(DIRB_1,OUTPUT);

  myservo.attach(SERVO_PIN);
  
  Serial.begin(9600);
}

void loop() {
/*
  if (!started) {
    while (getDistance() < 20) {
      Serial.println("Wait to start");
      delay(100);
    }
    started = true;
  }
*/
  long distance = getDistance();

  if (distance < 10) {
    
    backward(3000);
    turn(7000);
    
  } else {
    
    forward(100);
    
  }
  
}

// ----------- DIRECTION ---------

void forward(long duration) {
    Serial.println("forward");
    motorA(-1);
    motorB(-1);
    delay(duration);
}

void backward(long duration) {
    Serial.println("backward");
    motorA(1);
    motorB(1);
    delay(duration);
}

void turn(long duration) {
    Serial.println("turn");
    motorA(1);
    motorB(-1);
    delay(duration);
}


// ----------- SR04 ---------------

long getDistance() {
  long distance = sr04.Distance();
  Serial.print(distance);
  Serial.println("cm");

  return distance;
}


// ----------- SERVO ---------------


void servo(int angle) {
  myservo.write(angle);
}



// ------------ MOTORS --------------

void motorA(int direction) {
  motor(DIRA_1, DIRA_2, direction);
}

void motorB(int direction) {
  motor(DIRB_1, DIRB_2, direction);
}

void motor(int dir1, int dir2, int direction) {
  if (direction == 1) {
    digitalWrite(dir1,HIGH);
    digitalWrite(dir2,LOW); 
  } else if (direction == -1) {
    digitalWrite(dir1,LOW);
    digitalWrite(dir2,HIGH);
  } else {
    digitalWrite(dir1,LOW);
    digitalWrite(dir2,LOW); 
  }
}
