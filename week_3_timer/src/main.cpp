// Week3-Lecture2
// Timer Interrupt (Internal)
// Embedded IoT System Fall-2026

// Name: Tayyaba              Reg#: 1094

#include <Arduino.h>

#define LED 4

hw_timer_t *My_timer = NULL;

void ARDUINO_ISR_ATTR onTimer() {           // ARDUINO_ISR_ATTR == IRAM_ATTR
  digitalWrite(LED, !digitalRead(LED));     // safe in ISR on ESP32
}

void setup() {
  pinMode(LED, OUTPUT);

  // 1 MHz timer tick (1 tick = 1 µs) it is the starting frequency
  My_timer = timerBegin(1000000);   

  // attach ISR (new signature: no edge/level arg)
  timerAttachInterrupt(My_timer, &onTimer);

  // call ISR every 1,000,000 µs; autoreload=true; unlimited reloads (0)
  timerAlarm(My_timer, 1000000, true, 0);
}
void loop() {
  // nothing needed, all handled by interrupts
}