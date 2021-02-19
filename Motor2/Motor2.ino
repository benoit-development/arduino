#include <Servo.h>
#include <TaskScheduler.h>
#include <TaskSchedulerDeclarations.h>
#include <TaskSchedulerSleepMethods.h>

#define IMPACT_DISTANCE 20

Scheduler taskManager;



// SERVO

Servo servo;

void servoMethod() {
    servo.write(30);
    delay(500);
    servo.write(150);
    delay(500);
}
Task servoTask (1 * TASK_MILLISECOND, TASK_FOREVER, &servoMethod);







// ULTRASONIC SENSORS

int echoUp = A4;
int trigUp = A5;

int echoDown = A8;
int trigDown = A9;

void distanceUpMethod() {
    int distance = distanceTest(echoUp, trigUp);
    Serial.print("Up : ");
    Serial.println(distance);

    if (distance <= IMPACT_DISTANCE) {
        escape();
    }
}
Task distanceUpTask (1000 * TASK_MILLISECOND, TASK_FOREVER, &distanceUpMethod);
void distanceDownMethod() {
    int distance = distanceTest(echoUp, trigUp);
    Serial.print("Down : ");
    Serial.println(distance);

    if (distance <= IMPACT_DISTANCE) {
        escape();
    }
}
Task distanceDownTask (1000 * TASK_MILLISECOND, TASK_FOREVER, &distanceDownMethod);

int distanceTest(int echo, int trig) {
  digitalWrite(trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(trig, LOW);   
  float Fdistance = pulseIn(echo, HIGH);  
  Fdistance = Fdistance / 58;       
  return (int) Fdistance;
}




// MOVEMENTS

void escape() {
    Serial.println("A WALL ! ESCAPE !!!!");
    distanceUpTask.disable();
    distanceDownTask.disable();
    servoTask.disable();
    delay(2000);
}



// MAIN

void setup() {
    Serial.begin(9600);

    pinMode(echoUp, INPUT);
    pinMode(trigUp, OUTPUT);
    pinMode(echoDown, INPUT);
    pinMode(trigDown, OUTPUT);
    
    servo.attach(3,700,2400);

    taskManager.init();
    taskManager.addTask(distanceUpTask);
    distanceUpTask.enable();
    taskManager.addTask(distanceDownTask);
    distanceDownTask.enable();
    taskManager.addTask(servoTask);
    servoTask.enable();

    servo.write(30);
}

void loop() {
    taskManager.execute();
}


