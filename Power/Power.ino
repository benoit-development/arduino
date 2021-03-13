// **** INCLUDES *****
#include "LowPower.h"

// Use pin 2 as wake up pin
const int wakeUpPin = 2;

void wakeUp()
{
    // Just a handler for the pin interrupt.
  Serial.println("wakeup");
}

void setup()
{
    // Configure wake up pin as input.
    // This will consumes few uA of current.
    pinMode(wakeUpPin, INPUT);   
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop() 
{
  Serial.println("loop");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);

  Serial.println("attach");

    // Allow wake up pin to trigger interrupt on low.
    attachInterrupt(0, wakeUp, HIGH);
    
  Serial.println("powerDown");
    // Enter power down state with ADC and BOD module disabled.
    // Wake up when wake up pin is low.
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
    
  Serial.println("detach");
    // Disable external pin interrupt on wake up pin.
    detachInterrupt(0); 
    
    // Do something here
    // Example: Read sensor, data logging, data transmission.

}
