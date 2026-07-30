 **# ESP32_LDR-Smart-Light-Sensor_ThingSpeak-IoT-Cloud** 

**OBJECTIVE:**  

To develop an ESP32-based IoT Smart Light Control System that automatically detects ambient light using an LDR sensor, controls an LED and buzzer based on light intensity, and uploads real-time monitoring data to the ThingSpeak Cloud via Wi-Fi.

**OPERATION:**

The ESP32 continuously reads the ambient light intensity using an LDR sensor. The measured analog value is compared with a predefined threshold to determine whether the environment is Bright or Dark. When darkness is detected, the ESP32 automatically turns ON the LED and buzzer to indicate low-light conditions; otherwise, both remain OFF. Simultaneously, the current LDR value and light status are displayed on a 16×2 I2C LCD. Every 20 seconds, the ESP32 uploads the LDR reading and system status to the ThingSpeak IoT Cloud via Wi-Fi, enabling real-time remote monitoring and visualization of sensor data.

**SKETCH/CODE WORKING PRINCIPLE:**

**A. Library Files**:

#include <WiFi.h>

#include "ThingSpeak.h"

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

WiFi.h → Connects ESP32 to the Wi-Fi network.

ThingSpeak.h → Sends sensor data to the ThingSpeak IoT Cloud.

Wire.h → Enables I2C communication.

LiquidCrystal_I2C.h → Controls the 16×2 I2C LCD.

**B. GPIO Pin Definitions:**

#define LDR_PIN 34

#define LED_PIN 26

#define BUZZER_PIN 27

Defines which ESP32 GPIO pins are connected to:

GPIO34 → LDR Sensor

GPIO26 → LED

GPIO27 → Buzzer

**C. LCD Object:**

LiquidCrystal_I2C lcd(0x27,16,2);

Creates a 16×2 I2C LCD object with I2C address 0x27.

**D. Threshold Value:**

int threshold = 1800;

This is the reference value used to distinguish between Bright and Dark conditions.

LDR Value > 1800 → Dark

LDR Value ≤ 1800 → Bright

**E. Wi-Fi Credentials:**

const char* ssid

const char* password

Stores the Wi-Fi network name and password.

**F. ThingSpeak Information:**

channelID

writeAPIKey

These identify your ThingSpeak channel and authorize uploading data.

**G. WiFi Client:**

WiFiClient client;

Creates a communication client used by ThingSpeak.

**H. Upload Timer:**

unsigned long lastUpload = 0;

Stores the last upload time so that data is uploaded every 20 seconds, preventing unnecessary requests.

**setup() Function**

**1. Start Serial Monitor:**

Serial.begin(115200);

Starts serial communication for debugging.

**2. Configure Output Pins:**

pinMode(LED_PIN,OUTPUT);

pinMode(BUZZER_PIN,OUTPUT);

Sets LED and buzzer pins as outputs.

**3. Initialize LCD:**

lcd.init();

lcd.backlight();

Turns on and initializes the LCD.

**Displays:**

Smart Light

Monitoring

for 2 seconds.

**4. Connect ESP32 to Wi-Fi:**

WiFi.begin(...)

Keeps checking until the ESP32 connects successfully.

**5. Initialize ThingSpeak:**

ThingSpeak.begin(client);

Prepares ESP32 to communicate with the ThingSpeak Cloud.

**loop() Function**

**Step 1: Read LDR Value:**

int ldrValue = analogRead(LDR_PIN);

Reads the analog voltage from the LDR (0–4095).

**Step 2: Print Value:**

Serial.println(ldrValue);

Displays the current sensor reading in the Serial Monitor.

**Step 3: Compare with Threshold::**

if(ldrValue > threshold)

ESP32 decides whether the room is Dark or Bright.

If Dark, then 

    LED ON
   
    Buzzer ON

**LCD shows:**

    ROOM DARK

    LED ON

**Also stores:**

lightStatus = 1;

If Bright

    LED OFF
 
    Buzzer OFF

**LCD shows:**

    ROOM BRIGHT
    
     LED OFF

**Stores:**

lightStatus = 0;

**Step 4: Upload Data to ThingSpeak:**

Every 20 seconds:

ThingSpeak.setField(1, ldrValue);

ThingSpeak.setField(2, lightStatus);

**Uploads:**

Field 1 → LDR Value

Field 2 → Light Status

**Step 5: Check Upload Status:**

ThingSpeak.writeFields(...)

Response 200 → Upload Successful

Otherwise → Displays Error Code

**Step 6: Repeat:**

delay(500);

The loop repeats every 500 ms, while cloud updates occur every 20 seconds.
