
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad(
  makeKeymap(hexaKeys),
  rowPins,
  colPins,
  ROWS,
  COLS
);

#define WHITE 30
#define RED 31
#define GREEN 32
#define BLUE 33

void setup() {
  Serial.begin(9600);

  pinMode(WHITE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);

    if (customKey == '1') {
      led(HIGH, 0, 0, 0);
    }
    else if (customKey == '2') {
      led(0, 1, 0, 0);
    }
    else if (customKey == '3') {
      led(1, 1, 0, 0);
    }
    else if (customKey == '4') {
      led(0, 0, 1, 0);
    }
    else if (customKey == '5') {
      led(1, 0, 1, 0);
    }
    else if (customKey == '6') {
      led(0, 1, 1, 0);
    }
    else if (customKey == '7') {
      led(1, 1, 1, 0);
    }
    else if (customKey == '8') {
      led(0, 0, 0, 1);
    }
    else if (customKey == '9') {
      led(1, 0, 0, 1);
    }
  }
}

void led(int white, int red, int green, int blue) {
  digitalWrite(WHITE, white);
  digitalWrite(RED, red);
  digitalWrite(GREEN, green);
  digitalWrite(BLUE, blue);
}
