#include "LedControl.h"
#include "myLcd.h"
#include <TaskScheduler.h>
#include <TaskSchedulerDeclarations.h>
#include <TaskSchedulerSleepMethods.h>
#include "pitches.h"

LedControl lc = LedControl(12, 10, 11, 1);
Scheduler taskManager;

#define BUZZER_PIN 9


int startTimeCountDown = millis();


int getRemaining() {
    return (2 - ((millis() - startTimeCountDown) / 1000));
}



void countDown() {
    int elapsedMillis = getRemaining();

    Serial.println(elapsedMillis);
    display(lc, elapsedMillis);
}
void stopCountDown() {
    Serial.println("CountDown Disabled");
    lc.clearDisplay(0);
}
Task countDownTask (100 * TASK_MILLISECOND, TASK_FOREVER, &countDown, __null, false, __null, &stopCountDown);



int music[10][3][2] = {
    {
        {NOTE_C6, 1},
        {NOTE_C6, 1},
        {NOTE_C6, 2}
    },
    {
        {NOTE_G5, 1},
        {NOTE_G5, 1},
        {NOTE_G5, 2},
    },
    {
        {NOTE_E5, 1},
        {NOTE_E5, 1},
        {NOTE_E5, 2}
    },
    {
        {NOTE_C5, 3},
        {NOTE_C5, 1}
    },
    {
        {NOTE_C6, 3},
        {NOTE_B5, 9}
    },
    {
        {NOTE_A5, 1},
        {NOTE_A5, 1},
        {NOTE_A5, 2}
    },
    {
        {NOTE_F5, 1},
        {NOTE_F5, 1},
        {NOTE_F5, 2}
    },
    {
        {NOTE_D5, 1},
        {NOTE_D5, 1},
        {NOTE_D5, 2}
    },
    {
        {NOTE_A4, 3},
        {NOTE_A4, 1}
    },
    {
        {NOTE_A5, 3},
        {NOTE_G5, 9}
    }
};
int currentNotes = 0;


void playNote(int note, int duration) {
    tone(BUZZER_PIN, note, 1000);
    delay(duration * 140);
    noTone(BUZZER_PIN);
}

void playValentina() {
    Serial.println("Playing Valentina");
    currentNotes = (currentNotes + 1) % 9;
    Serial.println(currentNotes);

    for (int i=0; i<3; i++) {
        playNote(music[currentNotes][i][0], music[currentNotes][i][1]);
    }
}
Task valentinaTask (100 * TASK_MILLISECOND, TASK_FOREVER, &playValentina, __null, false, __null, __null);





void checkDoor() {
    if (isDoorClosed()) {
        countDownTask.disable();
        valentinaTask.disable();

    } else if (!countDownTask.isEnabled() && !valentinaTask.isEnabled()) {
        startTimeCountDown = millis();
        countDownTask.enable();
        Serial.println("Opened");

    } else if (countDownTask.isEnabled() && getRemaining() <= 0) {
        Serial.println("Play Valentina");
        valentinaTask.enable();
        countDownTask.disable();
    }
}
Task checkDoorTask (500 * TASK_MILLISECOND, TASK_FOREVER, &checkDoor);

bool isDoorClosed() {
    return !digitalRead(8);
}




void setup()
{
    Serial.begin(9600);

    lc.shutdown(0, false);
    lc.setIntensity(0, 3);
    lc.clearDisplay(0);
    pinMode(8, INPUT_PULLUP);

    taskManager.init();
    taskManager.addTask(countDownTask);
    taskManager.addTask(valentinaTask);
    taskManager.addTask(checkDoorTask);

    valentinaTask.disable();
    countDownTask.disable();
    checkDoorTask.enable();
}

void loop()
{
    taskManager.execute();
}