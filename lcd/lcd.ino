
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define TEMP_PIN 0
#define PHOTO_PIN 1

void setup()
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("Cels    Photo");
    Serial.begin(9600);
}

void loop()
{

    int tempReading = analogRead(TEMP_PIN);
    double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK)) * tempK);
    int tempC = (int) tempK - 273.15;
    int tempF = (int) (tempC * 9.0) / 5.0 + 32.0;

    int photocellReading = analogRead(PHOTO_PIN);

    lcd.setCursor(0, 1);
    lcd.print(tempC);
    Serial.println(tempC);


    lcd.setCursor(8, 1);
    lcd.print(photocellReading);
    Serial.println(photocellReading);

    delay(500);
}
