// Made by https://retroetgeek.com
#include <SoftwareSerial.h> // librairie pour creer une nouvelle connexion serie max 9600 baud
#define PIN_LED 13

SoftwareSerial BTSerial(10, 11); // RX | TX  = > BT-TX=10 BT-RX=11

void setup()
{
  Serial.begin(9600);


  BTSerial.begin(115200);

  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  String message;

  while (BTSerial.available())
  {
    message = BTSerial.readString();
    Serial.println(message);
  }

  while (Serial.available())
  {
    message = Serial.readString();
    BTSerial.println(message);
  }

  if (message == "on")
  {
    Serial.println("light on");
    digitalWrite(PIN_LED, HIGH);
  }
  else if (message == "off")
  {
    Serial.println("light off");
    digitalWrite(PIN_LED, LOW);
  }
}