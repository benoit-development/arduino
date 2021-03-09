#include "LedControl.h"
#include "myLcd.h"
#include "door.h"
#include "music.h"



void startCountDown() {
    for (int i=9; i>=0; i--) {
        if (isDoorClosed()) {
            return;
        }
        display(i);
        delay(600);
    }
    playValentina();
}

void setup()
{
    Serial.begin(9600);

    lcSetup();
    doorSetup();
}

void loop()
{
    if (!isDoorClosed()) {
        startCountDown();
    }
}
