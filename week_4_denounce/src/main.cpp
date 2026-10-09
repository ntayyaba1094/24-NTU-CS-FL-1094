#include <Arduino.h>

// UPDATED: Matched to your exact diagram.json connections!
#define BUTTON_PIN 32  
#define LED_PIN    4   

volatile bool debounceActive = false;
volatile bool buttonPressed = false; 

hw_timer_t *debounceTimer = NULL;

// Using IRAM_ATTR to ensure compatibility with older Arduino cores
void IRAM_ATTR onDebounceTimer() {
  // If the button is still held down after 50ms, it's valid!
  if (digitalRead(BUTTON_PIN) == LOW) {
    buttonPressed = true; 
  }
  debounceActive = false;
}

void IRAM_ATTR onButtonISR() {
  if (!debounceActive) {
    debounceActive = true;
    timerWrite(debounceTimer, 0);
    timerAlarmWrite(debounceTimer, 50000, false);
    timerAlarmEnable(debounceTimer);
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT); 
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonISR, FALLING);

  debounceTimer = timerBegin(0, 80, true);
  timerAttachInterrupt(debounceTimer, &onDebounceTimer, true);
}

void loop() {
  if (buttonPressed) {
    buttonPressed = false; 
    
    // Toggle the LED state
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    Serial.println("Valid Button Press Confirmed! Toggling LED.");
  }
}
