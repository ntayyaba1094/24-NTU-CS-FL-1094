//Tayyaba_1094
//IoT embedded sysytems
// Dual LED PWM with independent fading and OLED monitor
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// LED pins
const int LED1_PIN = 18;
const int LED2_PIN = 19;

// Hardware PWM Channels (0 to 15 are available on ESP32)
const int LED1_CHANNEL = 0;
const int LED2_CHANNEL = 1;

// Different PWM frequencies
const uint32_t LED1_FREQ = 1000;
const uint32_t LED2_FREQ = 5000;

// 8-bit resolution: duty values from 0 to 255
const int PWM_RESOLUTION = 8;
const int MAX_DUTY = 255;

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Current duty-cycle values
int duty1 = 0;
int duty2 = 0;

// Independent fading directions
int direction1 = 1;
int direction2 = 1;

// Non-blocking update timers
unsigned long lastFade1 = 0;
unsigned long lastFade2 = 0;
unsigned long lastOLED = 0;

// Time intervals (in milliseconds) for execution pacing
const unsigned long FADE_INTERVAL_1 = 12;
const unsigned long FADE_INTERVAL_2 = 20;
const unsigned long OLED_INTERVAL = 150;

// Function to update the text information shown on the OLED screen
void updateOLED() {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    // Print Header Title
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("DUAL PWM MONITOR");

    // Print LED 1 Data
    display.setCursor(0, 16);
    display.print("LED1: ");
    //convert range into 0%-100%
    display.print((duty1 * 100 + 127) / 255);
    display.print("% F:");
    // Read the actual live hardware frequency
    display.print(ledcReadFreq(LED1_CHANNEL));
    display.println("Hz");

    // Print LED 2 Data
    display.setCursor(0, 32);
    display.print("LED2: ");
    display.print((duty2 * 100 + 127) / 255);
    display.print("% F:");
    display.print(ledcReadFreq(LED2_CHANNEL));
    display.println("Hz");

    display.setCursor(0, 50);
    display.println("PWM: 8-bit");

    display.display();
}

// Function to update the duty cycle of a given LED channel with independent fading
void updateFade(int &duty, int &direction, int ledChannel) {
    duty += direction;

    // Reverse fading direction if maximum or minimum thresholds are reached
    if (duty >= MAX_DUTY) {
        duty = MAX_DUTY;
        direction = -1;
    } else if (duty <= 0) {
        duty = 0;
        direction = 1;
    }
 
    // Apply the calculated brightness to the PWM hardware channel
    ledcWrite(ledChannel, duty);
}

void setup() {
    Serial.begin(115200);
    delay(200);

    Wire.begin(21, 22);

    // Configure PWM channels and attach them to physical pins
    ledcSetup(LED1_CHANNEL, LED1_FREQ, PWM_RESOLUTION);
    ledcAttachPin(LED1_PIN, LED1_CHANNEL);

    ledcSetup(LED2_CHANNEL, LED2_FREQ, PWM_RESOLUTION);
    ledcAttachPin(LED2_PIN, LED2_CHANNEL);

    // Set initial duty cycles to 0 (off)
    ledcWrite(LED1_CHANNEL, 0);
    ledcWrite(LED2_CHANNEL, 0);

    // Initialize OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println("ERROR: OLED initialization failed.");
        while (true) {
            delay(1000);
        }
    }

    display.clearDisplay();
    updateOLED();

    // Print initial status to Serial Monitor
    Serial.println("Dual LED PWM and OLED monitor ready.");
    Serial.printf("LED1 frequency: %lu Hz\n", (unsigned long)ledcReadFreq(LED1_CHANNEL));
    Serial.printf("LED2 frequency: %lu Hz\n", (unsigned long)ledcReadFreq(LED2_CHANNEL));
}

void loop() {
    unsigned long now = millis();

    // Update fading for LED1 and LED2 independently based on their respective intervals
    if (now - lastFade1 >= FADE_INTERVAL_1) {
        lastFade1 = now;
        updateFade(duty1, direction1, LED1_CHANNEL);
    }

    if (now - lastFade2 >= FADE_INTERVAL_2) {
        lastFade2 = now;
        updateFade(duty2, direction2, LED2_CHANNEL);
    }
 
    // Non-blocking timer block for the OLED Display Refresh
    if (now - lastOLED >= OLED_INTERVAL) {
        lastOLED = now;
        updateOLED();
    }
}
