TASK_2_read me
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
- ESP32 DevKitC v4 (Simulation) / DevKit V1 (Physical Hardware)
- 1x Red LED & 1x Green LED
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

### Core Architecture 
**LEDC Peripheral & Timer Resource Allocation:**
The ESP32 features an LED Control (LEDC) peripheral block with group hardware timers. Each hardware timer dictates a bound frequency and duty resolution.
* Multiple channels can bind to a single timer only if they share identical frequency requirements.
* To achieve independent frequencies (1 kHz and 5 kHz), our firmware splits the workload across two separate hardware channels. **Channel 0** is configured to 1000 Hz, while **Channel 1** operates at 5000 Hz.


### Wokwi
Project link: https://wokwi.com/projects/475214284407653377

### Evidence
- screenshots/task_1_hardware_circuit.jpg
- screenshots/task_1_wokwi_circuit.png
- screenshots/task_2_hardware_circuit.jpg
- screenshots/task2_wokwi_circuit.png
- screenshots/wokwi_running_oled.png
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


### Simulation vs. Physical Hardware Reflections
* **LED Pin Flipping:** In the simulation layout configuration file (`diagram.json`), the virtual connections route the Red LED to GPIO 19 and the Green LED to GPIO 18. This matches functional operation but flips code parameters relative to the hardware bench-test setup. On physical hardware, the layout is wired directly to match the firmware definitions so that the Red LED receives the 1 kHz wave channel structure.

* **Visual Display & Fading Fluidity:** The physical components present a clean, linear luminance variance. Inside the web-based simulation framework, the visual updates can appear slightly stepped or choppy if local computer processor overhead drops browser rendering cycles under heavy background activity.

* **Frequency Validation Limitations:** Both the 1 kHz and 5 kHz waveforms switch rapidly enough that flicker remains completely invisible to the naked human eye on both setups.