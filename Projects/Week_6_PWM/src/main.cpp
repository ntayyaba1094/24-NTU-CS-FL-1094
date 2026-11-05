//Tayyaba Noor
//24_NTU_CS_FL_1094
#include <Arduino.h>
 
// Saves the number 2 as the physical pin on the ESP32 where the LED light is connected.
constexpr uint8_t LED_PIN = 2;
//Sets the speed of the electricity pulses to 5000 times per second (5 kHz)
constexpr uint32_t PWM_FREQUENCY = 5000;
//Sets the accuracy scale to 8 bits. This gives you 256 different brightness steps 
//(from completely off to fully bright).
constexpr uint8_t PWM_RESOLUTION = 8;
// Sets the maximum duty cycle to 255, which corresponds to full brightness for an 8-bit resolution.
constexpr uint16_t PWM_MAX_DUTY = 255;
// Assigns the PWM channel to 0. This is an arbitrary choice, as you can use any available channel.
constexpr uint8_t PWM_CHANNEL = 0;
 
void setup()
{
    Serial.begin(115200);
 
    // Configures internal channel 0 with your chosen speed (5000) and resolution scale (8-bit).
    ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
    //Connects physical Pin 2 to internal channel 0 so the settings take effect on that pin.
    ledcAttachPin(LED_PIN, PWM_CHANNEL);
 
    // Starts the LED with a brightness of 0, meaning it starts completely turned off.
    ledcWrite(PWM_CHANNEL, 0);
    // Sends a text message to your computer screen saying the project has successfully started.

    Serial.println("ESP32 PWM LED Fade Started");
}
 
void loop()
{
    //A counting loop that starts a variable named duty at 0, 
    //increases it by 1 each time, and stops when it reaches 255.
    for (int duty = 0; duty <= PWM_MAX_DUTY; duty++)
    {
        //Updates the LED channel with the current brightness level of the counter.
        ledcWrite(PWM_CHANNEL, duty); // Use channel
        delay(10); // Reduced delay slightly so the fade isn't too slow (100ms * 255 = 25 seconds)
    }
 
    // A counting loop that does the opposite. It starts at 255, 
    //decreases by 1 each time, and stops when it hits 0.
    for (int duty = PWM_MAX_DUTY; duty >= 0; duty--)
    {
        //Updates the LED channel with the current decreasing brightness level.
        ledcWrite(PWM_CHANNEL, duty); // Use channel
        delay(10);
    }
}
