
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

byte draw[8] = {
  0b11111, 
  0b00001, 
  0b11101, 
  0b10001, 
  0b10001, 
  0b10111, 
  0b10000, 
  0b11111
};

char *wonders[] = {
   "BABYLON      ",
   "HALIKARNASSOS",
   "PETRA        ",
   "OLYMPIA      ",
   "BYZANTIUM    ",
   "ALEXANDRIA   ",
   "EPHESOS      ",
   "RHODOS       ",
   "SIRACUSA     ",
   "GIZAH        "
};

char *side[] = {
   "DAY  ",
   "NIGHT"
};

int BUTTON_PIN = 2;

void setup() {
  lcd.begin(16, 2);
  
  randomSeed(analogRead(3));

  lcd.createChar(0, draw);

  lcd.setCursor(0,0);
  lcd.write((uint8_t)0);
  lcd.setCursor(0,1);
  lcd.write((uint8_t)0);
  lcd.setCursor(15,0);
  lcd.write((uint8_t)0);
  lcd.setCursor(15,1);
  lcd.write((uint8_t)0);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(BUTTON_PIN) == LOW) {
    for (int i=0; i<20; i++) {
      lcd.setCursor(2,0);
      lcd.print(wonders[random(10)]);
      
      lcd.setCursor(2,1);
      lcd.print(side[random(2)]);
      
      lcd.setCursor(13,1);
      lcd.print(random(7) + 1);
      
      delay(12 * i);
    }
  }

}
