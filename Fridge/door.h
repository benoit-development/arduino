
void doorSetup() {
    pinMode(8, INPUT_PULLUP);
}

bool isDoorClosed() {
    return !digitalRead(8);
}