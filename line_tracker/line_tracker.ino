int R = 10;
int M = 4;
int L = 2;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(digitalRead(L));
  Serial.print("|");
  Serial.print(digitalRead(M));
  Serial.print("|");
  Serial.println(digitalRead(R));

  delay(1000);
}
