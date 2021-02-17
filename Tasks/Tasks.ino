#include <TaskScheduler.h>
#include <TaskSchedulerDeclarations.h>
#include <TaskSchedulerSleepMethods.h>


Scheduler taskManager; 

void blink13Method() {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
}

Task blink13 (1 * TASK_SECOND, TASK_FOREVER, &blink13Method);

void setup() {
    pinMode(13, OUTPUT);

    taskManager.init();
    taskManager.addTask(blink13);

    blink13.enable();
}

void loop() {
    taskManager.execute();
}