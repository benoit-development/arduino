#include <Servo.h>
#include <TaskScheduler.h>
#include <TaskSchedulerDeclarations.h>
#include <TaskSchedulerSleepMethods.h>

#define IMPACT_DISTANCE 30

Scheduler taskManager;

Servo servo;




// ULTRASONIC SENSORS

int echoUp = A4;
int trigUp = A5;

int echoDown = A8;
int trigDown = A9;

void distanceUpMethod()
{
    int angles[] = { 30, 50, 70, 90, 110, 130, 150, 130, 110, 90, 70, 50 };

    for (int i; i<sizeof(angles); i++) {
        int angle = angles[i];
        servo.write(angle);
        int distance = distanceTest(echoUp, trigUp);

        Serial.print("Up : ");
        Serial.println(distance);

        if (distance <= IMPACT_DISTANCE)
        {
            escape();
        }
    }
}
Task distanceUpTask(100 * TASK_MILLISECOND, TASK_FOREVER, &distanceUpMethod);
void distanceDownMethod()
{
    int distance = distanceTest(echoDown, trigDown);
    Serial.print("Down : ");
    Serial.println(distance);

    if (distance <= IMPACT_DISTANCE)
    {
        escape();
    }
}
Task distanceDownTask(100 * TASK_MILLISECOND, TASK_FOREVER, &distanceDownMethod);

int distanceTest(int echo, int trig)
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(20);
    digitalWrite(trig, LOW);
    float Fdistance = pulseIn(echo, HIGH);
    Fdistance = Fdistance / 58;
    return (int)Fdistance;
}











// MOVEMENTS

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#define LT_R digitalRead(10)
#define LT_M digitalRead(4)
#define LT_L digitalRead(2)

void forward(int duration)
{
    // Serial.println("Forward");

    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, HIGH); //set IN1 hight level
    digitalWrite(IN2, LOW);  //set IN2 low level
    digitalWrite(IN3, LOW);  //set IN3 low level
    digitalWrite(IN4, HIGH); //set IN4 hight level
    delay(duration);
}

void back(int duration)
{
    Serial.println("Back");

    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(duration);
}

void left(float angle)
{
    Serial.println("Left");

    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    delay(angle * 4.5); // convert angle in ms
}

void right(float angle)
{
    Serial.println("RIGHT");

    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    delay(angle * 4.5); // convert angle in ms
}

void freeze(int duration)
{
    Serial.println("Stop");

    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(duration);
}

int getRightDistance()
{
    int distance = getDistance(0);

    Serial.print("Right : ");
    Serial.println(distance);

    return distance;
}

int getLeftDistance()
{
    int distance = getDistance(180);

    Serial.print("Left : ");
    Serial.println(distance);

    return distance;
}

int getDistance(int angle) {
    servo.write(angle);
    delay(350);
    int distance = distanceTest(echoUp, trigUp);
}

void escape()
{
    Serial.println("A WALL ! ESCAPE !!!!");
    distanceDownTask.disable();
    distanceUpTask.disable();
    back(500);
    freeze(1);

    int rightDistance = getRightDistance();
    delay(500);
    int leftDistance = getLeftDistance();
    delay(500);

    if ((rightDistance <= IMPACT_DISTANCE) && (leftDistance <= IMPACT_DISTANCE))
    {
        escape();
    }
    else if (rightDistance > leftDistance)
    {
        right(90);
        distanceDownTask.enable();
        distanceUpTask.enable();
        forward(10);
    }
    else
    {
        left(90);
        distanceDownTask.enable();
        distanceUpTask.enable();
        forward(10);
    }
    delay(10);
}








// MAIN

void setup()
{
    Serial.begin(9600);

    pinMode(echoUp, INPUT);
    pinMode(trigUp, OUTPUT);
    pinMode(echoDown, INPUT);
    pinMode(trigDown, OUTPUT);

    servo.attach(3, 700, 2400);

    taskManager.init();
    taskManager.addTask(distanceUpTask);
    distanceUpTask.enable();
    taskManager.addTask(distanceDownTask);
    distanceDownTask.enable();

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    forward(10);
}

void loop()
{
    taskManager.execute();
}
