#include <Arduino.h>

int freqDelays[] = {500, 250, 100, 50, 33};  // ms for on/off periods (half-period for each freq)
int freqIndex = 0;
unsigned long previousMillis = 0;
int ledState = LOW;
unsigned long buttonPressTime = 0;
bool buttonPressed = false;
int currentDelay;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  Serial.begin(115200);
  currentDelay = freqDelays[freqIndex];
  Serial.print("Starting LED blink at ");
  float freq = 1000.0 / (2 * currentDelay);
  Serial.print(freq);
  Serial.println(" Hz. Short press IO0 to cycle, long press(>1s) to reset.");
}

void loop() {
  // Button handling
  if (digitalRead(0) == LOW) {
    if (!buttonPressed) {
      buttonPressed = true;
      buttonPressTime = millis();
    }
  } else {
    if (buttonPressed) {
      buttonPressed = false;
      unsigned long pressDuration = millis() - buttonPressTime;
      if (pressDuration >= 1000) {  // Long press: reset to 1Hz
        Serial.println("Reset Triggered!");
        freqIndex = 0;
      } else {  // Short press: cycle next
        freqIndex = (freqIndex + 1) % 5;
      }
      currentDelay = freqDelays[freqIndex];
      Serial.print("Switched to ");
      float newFreq = 1000.0 / (2 * currentDelay);
      Serial.print(newFreq);
      Serial.println(" Hz");
    }
  }

  // Non-blocking LED blink
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= currentDelay) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(2, ledState);
  }
}