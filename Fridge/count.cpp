#include <Arduino.h>
#include "door.h"
#include "lcd.h"
#include "music.h"

void stop() {
    clearDisplay();
}

void startCountDown() {
    for (int i=1; i>=0; i--) {
        if (isDoorClosed()) {
            stop();
            return;
        }
        display(i);
        delay(600);
    }
    playGameOfThrone();
}