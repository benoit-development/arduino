
int buttonApin = 9;
int buttonBpin = 8;
int LED = 13;

void setup() {
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  pinMode(buttonBpin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(buttonApin) == LOW) {
    analogWrite(LED, 255);
  }
  if (digitalRead(buttonBpin) == LOW) {
    digitalWrite(LED, LOW);
  }
}
