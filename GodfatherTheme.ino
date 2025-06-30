#include <LiquidCrystal.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int tempo = 80;
int buzzer = 9; // We're using Pin 9 (PB1)

// ----- NOTES -----
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C4  262
#define NOTE_C5  523
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define REST     0

// ----- MELODY -----
int melody[] = {
  REST, 4, REST, 8, REST, 8, REST, 8, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8,
  NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8, NOTE_G4, 8,
  NOTE_E4, 2, NOTE_E4, 8, NOTE_A4, 8, NOTE_C5, 8,
  NOTE_B4, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_C5, 8, NOTE_A4, 8, NOTE_E4, 8, NOTE_DS4, 8,
  NOTE_D4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8,
  NOTE_B4, 2, NOTE_D4, 8, NOTE_F4, 8, NOTE_GS4, 8,
  NOTE_A4, 2, NOTE_C4, 8, NOTE_C4, 8, NOTE_G4, 8,
  NOTE_F4, 8, NOTE_E4, 8, NOTE_G4, 8, NOTE_F4, 8, NOTE_F4, 8, NOTE_E4, 8, NOTE_E4, 8, NOTE_GS4, 8,
  NOTE_A4, 2, REST, 8, NOTE_A4, 8, NOTE_A4, 8, NOTE_GS4, 8,
  NOTE_G4, 2, NOTE_B4, 8, NOTE_A4, 8, NOTE_F4, 8,
  NOTE_E4, 2, NOTE_E4, 8, NOTE_G4, 8, NOTE_E4, 8,
  NOTE_D4, 2, NOTE_D4, 8, NOTE_D4, 8, NOTE_F4, 8, NOTE_DS4, 8,
  NOTE_E4, 2
};

int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  The Godfather");
  lcd.setCursor(0, 1);
  lcd.print("(C)Robson Couto");

  pinMode(buzzer, OUTPUT);

  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }

    int pitch = melody[thisNote];
    if (pitch == REST) {
      delay(noteDuration);
    } else {
      playToneAVR(pitch, noteDuration * 0.9);
      delay(noteDuration * 0.1);
    }
  }
}

void loop() {
  // only plays once
}

void playToneAVR(uint16_t frequency, uint16_t duration_ms) {
  uint32_t period_us = 1000000UL / frequency;
  uint32_t halfPeriod = period_us / 2;
  uint32_t totalCycles = (uint32_t)duration_ms * 1000UL / period_us;

  for (uint32_t i = 0; i < totalCycles; i++) {
    // Set Pin 9 HIGH (PB1)
    asm volatile (
      "sbi %[port], %[bit] \n"
      :
      : [port] "I" (_SFR_IO_ADDR(PORTB)), [bit] "I" (1)
    );

    delayMicroseconds(halfPeriod);

    // Set Pin 9 LOW
    asm volatile (
      "cbi %[port], %[bit] \n"
      :
      : [port] "I" (_SFR_IO_ADDR(PORTB)), [bit] "I" (1)
    );

    delayMicroseconds(halfPeriod);
  }
}