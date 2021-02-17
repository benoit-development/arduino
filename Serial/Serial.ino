
void setup() {
  Serial.begin(9600);
}

int count = 0;

void loop() {
  Serial.println(count++);
  delay(1000);
}
