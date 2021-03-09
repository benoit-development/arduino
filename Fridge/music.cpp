#include <Arduino.h>
#include "pitches.h"
#include "door.h"
#include "count.h"
#include "lcd.h"

#define BUZZER_PIN 9

int valentina[][2] = {
    {NOTE_C6, 1},
    {NOTE_C6, 1},
    {NOTE_C6, 2},
    
    {NOTE_G5, 1},
    {NOTE_G5, 1},
    {NOTE_G5, 2},
    
    {NOTE_E5, 1},
    {NOTE_E5, 1},
    {NOTE_E5, 2},
    
    {NOTE_C5, 3},
    {NOTE_C5, 1},
    
    {NOTE_C6, 3},
    {NOTE_B5, 9},
    {NOTE_A5, 1},

    {NOTE_A5, 1},
    {NOTE_A5, 2},

    {NOTE_F5, 1},
    {NOTE_F5, 1},
    {NOTE_F5, 2},

    {NOTE_D5, 1},
    {NOTE_D5, 1},
    {NOTE_D5, 2},

    {NOTE_A4, 3},
    {NOTE_A4, 1},

    {NOTE_A5, 3},
    {NOTE_G5, 9},
};

int gameOfThrone[][2] = {
    {NOTE_A4, 2},
    {NOTE_D4, 2},
    {NOTE_F4, 1},
    {NOTE_G4, 1},

    {NOTE_A4, 2},
    {NOTE_D4, 2},
    {NOTE_F4, 1},
    {NOTE_G4, 1},

    {NOTE_A4, 2},
    {NOTE_D4, 2},
    {NOTE_FS4, 1},
    {NOTE_G4, 1},

    {NOTE_A4, 2},
    {NOTE_D4, 2},
    {NOTE_FS4, 1},
    {NOTE_G4, 1},

    {NOTE_A4, 6},
    {NOTE_D4, 6},

    {NOTE_F4, 1},
    {NOTE_G4, 1},
    {NOTE_A4, 4},

    {NOTE_D4, 4},
    {NOTE_F4, 1},
    {NOTE_G4, 1},

    {NOTE_E4, 6},
};

void playNote(int note, int duration, int noteDurantion) {
    tone(BUZZER_PIN, note, 1000);
    delay(duration * noteDurantion);
    noTone(BUZZER_PIN);
}

void playMusic(int music[][2], int noteCount, int noteDurantion) {
    displayMusic();
    while (!isDoorClosed()) {
        for (int i=0; i<noteCount; i++) {
            if (isDoorClosed()) {
                stop();
                return;
            }
            playNote(music[i][0], music[i][1], noteDurantion);
        }
    }
}

void playValentina() {
    playMusic(valentina, 26, 140);
}

void playGameOfThrone() {
    playMusic(gameOfThrone, 25, 180);
}
