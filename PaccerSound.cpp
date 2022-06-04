/*
 * PaccerSound
 * =========
 * 
 * Library for managing sound for the Paccer Pinball.
 * 
 * Created 2022-06-04
 * 
 * https://github.com/PaccerPinball/PaccerSound
 */

#include <Arduino.h>
#include "PaccerSound.h"

PaccerSound::PaccerSound(const int& speakerPin, const int& tempo) {
    this->speakerPin = speakerPin;
    this->wholeNote = (60000 * 4) / tempo;
}

void PaccerSound::tick() {
    if (*currentTone == MELODY_END) return;
    if (nextTone > millis()) return;
    if (nextTone != 0) currentTone++;

    const int& frequency = *currentTone;

    if (frequency == MELODY_END) {
        serial("END OF MELODY");
        return;
    }

    currentTone++;

    serial("Playing next tone: " + String(frequency));

    int duration;
    if (*currentTone < 0) {
        duration = wholeNote / abs(*currentTone);
        duration *= 1.5;
    }
    else duration = wholeNote / *currentTone;

    tone(speakerPin, frequency, duration * 0.9);
    nextTone = millis() + duration;

}

void PaccerSound::melody(int *melody) {
    currentTone = melody;
    nextTone = 0;
}

void PaccerSound::serial(const String &msg) {
    Serial.println( "SOUND | " + msg);
}