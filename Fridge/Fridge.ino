#include "LedControl.h"
#include "lcd.h"
#include "door.h"
#include "music.h"
#include "count.h"
#include "LowPower.h"

const int wakeUpPin = 2;

void wakeUp()
{
    Serial.println("Wake up");
}

void setup()
{
    Serial.begin(9600);
    lcSetup();
    pinMode(wakeUpPin, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    Serial.println("loop");
    delay(1000);
    attachInterrupt(0, wakeUp, HIGH);
    Serial.println("Power Down");
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    Serial.println("Status Changed");
    detachInterrupt(0);


    Serial.println("Light up");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);

    if (!isDoorClosed())
    {
        Serial.println("Door is open");
        startCountDown();
    }
    else
    {
        Serial.println("Door is closed");
    }
}
