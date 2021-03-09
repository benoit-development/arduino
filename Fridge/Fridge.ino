#include "LedControl.h"
#include "lcd.h"
#include "door.h"
#include "music.h"
#include "count.h"


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
    delay(1000);
}
