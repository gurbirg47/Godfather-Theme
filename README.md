# Godfather-Theme
Godfather Theme Buzzer (AVR Assembly + Arduino)

This embedded systems project plays the Godfather theme using a piezo buzzer and 16x2 I2C LCD display, driven by an Arduino Uno. All tones are generated through direct I/O control using AVR assembly, providing low-level insight into signal generation and microcontroller programming.

Hardware Used
	•	Arduino Uno (ATmega328P)
	•	Piezo buzzer (connected to digital pin 9)
	•	16x2 I2C LCD Display (I2C address: 0x27)
	•	Breadboard and jumper wires
	•	USB cable for power and programming

Project Highlights
	•	Played the full Godfather theme by generating square waves manually, without using tone() or sound libraries.
	•	Controlled the buzzer output using AVR instructions sbi and cbi to toggle pin 9 (PB1) at calculated frequencies.
	•	Implemented musical timing based on a configurable tempo (80 BPM), calculating note durations from beat divisions.
	•	Displayed a custom startup message on a 16x2 LCD using the LiquidCrystal_I2C library.
	•	Used lcd.init(), lcd.backlight(), and lcd.setCursor() for display control.
	•	Stored melody and rhythm data in arrays and looped through them to sequentially output each note.
	•	Used playToneAVR() to manually generate tone signals and delayMicroseconds() to control waveform timing.
	•	Handled musical rests and durations using conditional logic and delay cycles.
	•	Focused on achieving timing accuracy and low-level signal control suitable for educational or demonstration purposes.

Key Functions Implemented
	•	setup(): Initializes the LCD display, sets up the buzzer pin, and plays the entire melody on startup.
	•	loop(): Left intentionally empty, as the melody plays only once.
	•	playToneAVR(frequency, duration_ms): Manually generates square wave signals using AVR instructions to control buzzer output.
	•	melody[]: Array storing the pitch and note duration structure of the song.
	•	Timing Calculations: Performed using note dividers and tempo to determine exact delays for each note.

Learning Outcomes
	•	Practiced low-level AVR programming and register-based control of digital I/O.
	•	Learned to generate sound without abstracted functions by manipulating timing and signal generation manually.
	•	Integrated peripheral devices (LCD) with real-time audio playback for multi-component microcontroller interaction.
	•	Developed a deeper understanding of waveform mechanics, delay loops, and hardware synchronization.