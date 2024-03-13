/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// the setup function runs once when you press reset or power the board
const int ledPin = LED_BUILTIN; // Use built-in LED pin for blinking

// Morse code definitions
const int dotDelay = 250; // Duration of dot in milliseconds
const int dashDelay = 3 * dotDelay; // Duration of dash (3 times dot)
const int interCharDelay = 3 * dotDelay; // Delay between characters (3 times dot)
const int interWordDelay = 7 * dotDelay; // Delay between words (7 times dot)

// Morse code dictionary
const char *morseCode[] = {
  ".-",    // A
  "-...",  // B
  "-.-.",  // C
  "-..",   // D
  ".",     // E
  "..-.",  // F
  "--.",   // G
  "....",  // H
  "..",    // I
  ".---",  // J
  "-.-",   // K
  ".-..",  // L
  "--",    // M
  "-.",    // N
  "---",   // O
  ".--.",  // P
  "--.-",  // Q
  ".-.",   // R
  "...",   // S
  "-",     // T
  "..-",   // U
  "...-",  // V
  ".--",   // W
  "-..-",  // X
  "-.--",  // Y
  "--.."   // Z
};

// Function to blink Morse code for a character
void blinkCharacter(char character) {
  int index = toupper(character) - 'A'; // Convert to uppercase and calculate index
  if (index >= 0 && index < 26) { // Ensure it's a valid character
    const char *code = morseCode[index];
    while (*code) {
      if (*code == '.') {
        digitalWrite(ledPin, HIGH);
        delay(dotDelay);
      } else if (*code == '-') {
        digitalWrite(ledPin, HIGH);
        delay(dashDelay);
      }
      digitalWrite(ledPin, LOW);
      delay(dotDelay); // Delay between dots and dashes
      code++;
    }
    delay(interCharDelay - dotDelay); // Delay between characters
  } else if (character == ' ') {
    delay(interWordDelay - interCharDelay); // Delay between words
  }
}

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  String input;
  Serial.println("Enter a word (letters only):");
  while (Serial.available() == 0); // Wait for input
  input = Serial.readStringUntil('\n'); // Read the input until newline character

  // Blink Morse code for each character in the input word
  for (int i = 0; i < input.length(); i++) {
    blinkCharacter(input.charAt(i));
  }
}
