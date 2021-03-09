#include "pitches.h"
#include "door.h"

#define BUZZER_PIN 9

int music[26][2] = {
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
    {NOTE_G5, 9}
};

int currentNotes = 0;

void playValentina() {
    Serial.println("Playing Valentina");
    currentNotes = (currentNotes + 1) % 9;
    Serial.println(currentNotes);

    for (int i=0; i<26; i++) {
        if (isDoorClosed()) {
            return;
        }
        playNote(music[currentNotes][0], music[currentNotes][1], 140);
    }
}

void playNote(int note, int duration, int rythm) {
    tone(BUZZER_PIN, note, 1000);
    delay(duration * rythm);
    noTone(BUZZER_PIN);
}
