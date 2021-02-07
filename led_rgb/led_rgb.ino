
int RED = 13;
int GREEN = 8;
int BLUE = 2;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for (int i=0; i<255; i++) {
    analogWrite(RED, i);
    delay(10);
  }
  for (int i=0; i<255; i++) {
    analogWrite(GREEN, i);
    delay(10);
  }
  for (int i=0; i<255; i++) {
    analogWrite(BLUE, i);
    delay(10);
  }
}
