//Tayyaba Noor
//24_NTU_CS_FL_1094
//Tayyaba Noor
//24_NTU_CS_FL_1094

#include <Arduino.h>
 
constexpr uint8_t LED_PIN = 2;
constexpr uint32_t PWM_FREQUENCY = 5000;
constexpr uint8_t PWM_RESOLUTION = 8;
constexpr uint16_t PWM_MAX_DUTY = 255;
constexpr uint8_t PWM_CHANNEL = 0;
 
void setup()
{
    Serial.begin(115200);
 
    // 2. Modified for older ESP32 Core compatibility 
    ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(LED_PIN, PWM_CHANNEL);
 
    ledcWrite(PWM_CHANNEL, 0); // Use channel here, not the pin
    Serial.println("ESP32 PWM LED Fade Started");
}
 
void loop()
{
    for (int duty = 0; duty <= PWM_MAX_DUTY; duty++)
    {
        ledcWrite(PWM_CHANNEL, duty); // Use channel
        delay(10); // Reduced delay slightly so the fade isn't too slow (100ms * 255 = 25 seconds)
    }
 
    for (int duty = PWM_MAX_DUTY; duty >= 0; duty--)
    {
        ledcWrite(PWM_CHANNEL, duty); // Use channel
        delay(10);
    }
}
