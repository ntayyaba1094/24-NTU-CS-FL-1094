#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Screen Dimensions
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button pin
const int BUTTON_PIN = 18; 

// Non-Blocking Debounce Variables
int lastStableButtonState = HIGH;  // The verified structural state of the button
int lastFlickerReading = HIGH;     // The raw hardware reading from the last loop execution
unsigned long lastDebounceTime = 0;  // Holds the timestamp when a bounce ripple occurred
const unsigned long DEBOUNCE_DELAY = 50; // Filter stability window in milliseconds

// Application State Variables
int pressCounter = 0;
bool isButtonPressed = false;

// Refreshes the display template with current data
void updateOLED(bool pressedState, int count) {
  display.clearDisplay();
  
  // Header Style
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(12, 0);
  display.println("ESP32 STATUS TRACKER");
  display.drawFastHLine(0, 10, 128, SSD1306_WHITE);
  
  // Button Status String
  display.setCursor(0, 20);
  display.print("Button: ");
  if (pressedState) {
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Inverted text highlight
    display.print(" PRESSED  ");
  } else {
    display.setTextColor(SSD1306_WHITE);
    display.print(" RELEASED ");
  }
  
  // Counter Layout
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 44);
  display.print("Count: ");
  display.print(count);
  
  display.display();
}

void setup() {
  Serial.begin(115200);
  
  // Configure input with internal pull-up resistor (LOW when pressed)
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Wire.begin(21, 22);
  
  // Initialize I2C OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED Initialization Failed!"));
    for(;;); // Halt application execution
  }
  
  Serial.println("System initialized successfully.");
  updateOLED(isButtonPressed, pressCounter);
}

void loop() {
  // 1. Fetch current instantaneous value of the pin
  int currentRawReading = digitalRead(BUTTON_PIN);

  // 2. If the physical contact bounces, reset the validation timer
  if (currentRawReading != lastFlickerReading) {
    lastDebounceTime = millis();
  }

  // 3. Evaluate if the pin signal has been perfectly quiet for the duration window
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    
    // Check if the validated signal indicates an actual logical change
    if (currentRawReading != lastStableButtonState) {
      lastStableButtonState = currentRawReading;

      // the falling edge (from HIGH to LOW==Pressed down)
      if (lastStableButtonState == LOW) {
        isButtonPressed = true;
        pressCounter++;
        
        Serial.print("[EVENT] Stable Press Verified. Count: ");
        Serial.println(pressCounter);
        
        updateOLED(isButtonPressed, pressCounter);
      } 
      // the rising edge (from LOW to HIGH ==Let go)
      else {
        isButtonPressed = false;
        Serial.println("[EVENT] Button Released.");
        updateOLED(isButtonPressed, pressCounter);
      }
    }
  }

  // Preserve the immediate raw sample for the next loop pass
  lastFlickerReading = currentRawReading;
}
