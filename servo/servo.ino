#define LED 13
#define RIGHT 12
#define LEFT 2

#include <Servo.h>
Servo myservo;

void setup() {
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  myservo.attach(9);
  myservo.write(60);
}

void loop() {
  if (digitalRead(LEFT) == LOW) {
    digitalWrite(LED, HIGH);
  myservo.write(90);
  }
  if (digitalRead(RIGHT) == LOW) {
    digitalWrite(LED, LOW);
  myservo.write(30);
  }
}
