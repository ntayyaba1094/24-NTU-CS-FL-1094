
# Embedded IoT Homework 2
## Dual PWM LED Control with OLED Monitoring

**Course:** Embedded IoT Systems

### Objective
### Task 1
Control two LEDs using independent PWM outputs with different
frequencies.
### Task 2
 Display the current duty-cycle percentages and
configured frequencies on an SSD1306 I2C OLED.

### Components
- ESP32 DevKit V1
- Two LEDs
- Two 220-ohm current-limiting resistors
- SSD1306 128x64 I2C OLED
- Breadboard and jumper wires

### Wiring

| Component                            | ESP32 connection |
|--------------------------------------|------------------|
| LED 1 anode through 220-ohm resistor | GPIO 18          |
| LED 1 cathode                        | GND              |
| LED 2 anode through 220-ohm resistor | GPIO 19          |
| LED 2 cathode                        | GND              |
| OLED SDA                             | GPIO 21          |
| OLED SCL                             | GPIO 22          |
| OLED VCC                             | 3.3V             |
| OLED GND                             | GND              |

### PWM Configuration

| LED | GPIO | Frequency | Resolution |
|-----|-----:|----------:|-----------:|
|LED 1| 18   | 1000 Hz   | 8-bit      |
|LED 2| 19   | 5000 Hz   | 8-bit      |

The duty-cycle value ranges from 0 to 255.
Percentage = duty value / 255 * 100.

PWM duty cycle controls the apparent brightness of each LED.
PWM frequency determines the number of switching cycles per second.

### OLED Monitoring
The SSD1306 display shows the live duty-cycle percentage and configured PWM frequency for both LEDs.

### Wokwi
Project link: https://wokwi.com/projects/475214284407653377

### Evidence
- screenshots/task1_wokwi_circuit.png
- screenshots/task1_wokwi_runing.png
- screenshots/task_1_hardware_circuit.jpg
- screenshots/task2_wokwi_circuit.png
- screenshots/task2_wokwi_running_oled.png
- screenshots/hardware_circuit.jpg
- screenshots/hardware_oled_output.jpg

### Test Results

Task 1: Dual-LED Fading with Different PWM Frequencies

 Wokwi: PASSED
The code starts smoothly without errors. The Red LED (on GPIO 18) and the Green LED (on GPIO 19) both fade up and down completely independently. Because of the non-blocking millis() timers, the two fade intervals (12ms vs 20ms) run side by side without stalling each other.

 Physical hardware: PASSED
The script uploaded perfectly to my physical ESP32 board. The serial monitor (set at 115200 baud) confirms the initialization text, showing that Channel 0 is successfully generating a crisp 10 kHz wave for LED1 and Channel 1 is pushing a 5 kHz wave for LED2. The physical LEDs fade continuously without any jerky movements.



Task 2: Integrating the SSD1306 OLED Monitor

• Wokwi: PASSED
After updating the code to use the newer ledcAttach() structure for Task 2, the I2C OLED screen at address 0x3C activates perfectly. The display shows the static headers and outputs the live duty cycle percentages (scaling smoothly from 0% to 100%). The ledcReadFreq() function reads back the custom v3.x parameters—1000Hz for LED1 and 5000Hz for LED2—and updates them on-screen in real time every 150ms.
• Physical hardware: PASSED
The circuit was rebuilt on the physical breadboard by hooking up the OLED's SDA to GPIO 21 and SCL to GPIO 22. The screen switches on immediately upon boot. The 8-bit math updates perfectly, and the text stays clean and readable without any screen tearing, all while the LEDs keep fading in the background at their original pacing.


### Simulation vs Hardware
LED Pin Flipping: In the simulation configuration (diagram.json), the Red LED is linked to GPIO 19 and the Green LED is linked to GPIO 18. This reverses the code definitions (LED1_PIN = 18, LED2_PIN = 19), meaning the Green LED cycles faster than the Red LED. On the physical hardware breadboard, the pins can be wired exactly to match the code variables so that the Red LED receives the 10 kHz signal.

Fading Smoothness & Intensity: The physical LEDs exhibit an organic, linear-looking glow transition across the duty cycle scope. In the Wokwi simulation interface, the fading jumps can occasionally look slightly stepped or choppy if the web browser encounters rendering frame drops under high local CPU usage.

Frequency Perception: Both the 5 kHz and 10 kHz frequencies are completely invisible to the human eye as raw flicker, looking like smooth dimming on both platforms. However, the 10 kHz and 5 kHz hardware frequencies can be mathematically captured on real hardware using an oscilloscope or logic analyzer, whereas Wokwi relies purely on internal logic emulation.
