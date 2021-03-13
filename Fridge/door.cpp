#include <Arduino.h>

bool isDoorClosed() {
    return !digitalRead(2);
}