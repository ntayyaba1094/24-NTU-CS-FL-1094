// Week3-Lecture2
// Timer Interrupt (Internal)
// Embedded IoT System Fall-2026

// Name: Tayyaba              Reg#: 1094

#include <Arduino.h>

#define LED 4

hw_timer_t *My_timer = NULL;
//HW_TIMER Yeh ESP32 ka ek khas data type hai,jo hardware timer ki configurations aur uski details ko sambhalta hai.
//My_timer ek pointer hai jo hardware timer ko point karta hai,aur iske zariye hum timer ki settings aur interrupts ko manage karte hain.
void ARDUINO_ISR_ATTR onTimer() {           
  digitalWrite(LED, !digitalRead(LED));     
}
//Yeh code ESP32 par ek timer interrupt chalata hai jo LED ka status badalta hai.
//Jab bhi timer trigger hota hai, yeh LED ko ON ya OFF (toggle) karta hai.

void setup() {
  pinMode(LED, OUTPUT); 
  // Yeh aapke LED pin ko OUTPUT(on/off) mode mein set karta hai 

  My_timer = timerBegin(1000000);   
  //Yeh timer ko 1 MHz (1,000,000 Hz) ki frequency par shuru (initialize) karta hai.
  
  timerAttachInterrupt(My_timer, &onTimer);
  //Yeh timer ke sath ek Interrupt Service Routine function jorta hai.
  timerAlarm(My_timer, 1000000, true, 0);
  //Yeh alarm ki timing aur uski setting tay karta hai
}
void loop() {
  // nothing needed, all handled by interrupts
}