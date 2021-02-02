int LED = 13;
int counter = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  counter++;

  String output = "Blink number : ";
  Serial.println(output + counter);
  
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(250);

}
