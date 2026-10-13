
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
);

void setup() {
    Serial.begin(115200);

    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("OLED initialization failed!");
        while (true) {
            delay(100);
        }
    }

    //Wipes the secret digital memory background of the screen completely black
    display.clearDisplay();
    //Sets the text size to standard scale level 1 (small and crisp).
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    //cursor at the absolute top-left corner coordinate (0,0) of the screen
    display.setCursor(0, 0);
    //prints the text to the screen buffer, which will be displayed when display.display() is called
    display.println("ESP32 + OLED");
    display.println("PlatformIO Ready!");
    display.println("I2C Address: 0x3C");

    //now it will display the text on the screen
    display.display();
    
    Serial.println("OLED initialized successfully.");
}

void loop() {
    // Add your application code here.
    display.clearDisplay();
    display.setTextSize(1.5);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 20);
    display.println("Hello, World!");
    display.display();
}

