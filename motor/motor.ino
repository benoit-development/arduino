//www.elegoo.com


#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

//    The direction of the car's movement
//  ENA   ENB   IN1   IN2   IN3   IN4   Description  
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Car is runing forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Car is runing back
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Car is turning left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Car is turning right
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Car is stoped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Car is stoped
//  LOW   LOW   N/A   N/A   N/A   N/A   Car is stoped


//define L298n module IO Pin
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

// Utrasonic sensor
#define DISTANCE 20

//Line Tracking IO define
#define LT_R digitalRead(10)
#define LT_M digitalRead(4)
#define LT_L digitalRead(2)

//Servo
int Echo = A4;  
int Trig = A5;
int rightDistance = 0, leftDistance = 0, middleDistance = 0;



//before execute loop() function, 
//setup() function will execute first and only execute once
void setup() {
  myservo.attach(3,700,2400);  // attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  myservo.write(90);
  freeze(100);
}

//Repeat execution
void loop() {
  
    middleDistance = Distance_test();

    if (middleDistance <= DISTANCE) {

      back(500);
      freeze(1);
      
      checkRightDistance();
      delay(500);
      checkLeftDistance();
      delay(500);
      myservo.write(90);
      
      if((rightDistance <= DISTANCE) && (leftDistance <= DISTANCE)) {
        back(200);
      } else if(rightDistance > leftDistance) {
        right(90);
      }
      else if(rightDistance <= leftDistance) {
        left(90);
      }
      
    } else {
      forward(10);
    }
    delay(10);
    
}

void forward(int duration){ 
  // Serial.println("Forward");
  
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,HIGH); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,HIGH); //set IN4 hight level
  delay(duration);
}

void back(int duration){
  Serial.println("Back");
  
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(duration);
}

void left(float angle){
  Serial.println("Left");
  
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 

  delay(angle * 4.5); // convert angle in ms
}

void right(float angle){
  Serial.println("RIGHT");
  
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW); 

  delay(angle * 4.5); // convert angle in ms
}

void freeze(int duration){
  Serial.println("Stop");
  
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  delay(duration);
}

//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int) Fdistance;
}

void checkMiddleDistance() {
  //middle
  myservo.write(90);
  delay(500); 
  middleDistance = Distance_test();

  Serial.print("Middle : ");
  Serial.println(middleDistance);
}

void checkRightDistance() {
  //right
  myservo.write(0);
  delay(500); 
  rightDistance = Distance_test();

  Serial.print("Right : ");
  Serial.println(rightDistance);
}

void checkLeftDistance() {
  //middle
  myservo.write(180);
  delay(500); 
  leftDistance = Distance_test();

  Serial.print("Left : ");
  Serial.println(leftDistance);
}
