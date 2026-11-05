#include <Arduino.h>

#define DAC_PIN 25

void setup()
{
    Serial.begin(115200);
    Serial.println("ESP32 DAC LED Test Started");
    
    // Explicitly enable the DAC on pin 25
    // Note: If compilation fails on this line depending on your board package, 
    // you can safely comment it out or delete it.
    #ifdef SOC_DAC_SUPPORTED
    #endif
}

void loop()
{
    int values[] = {0, 64, 128, 192, 255};

    for (int i = 0; i < 5; i++)
    {
        // Try standard or fallback dacWrite
        dacWrite(DAC_PIN, values[i]);

        Serial.print("DAC Value: ");
        Serial.println(values[i]);

        delay(2000);
    }
}
