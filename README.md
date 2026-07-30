 # ESP32_LDR-Smart-Light-Sensor_ThingSpeak-IoT-Cloud  

OBJECTIVE  

To develop an ESP32-based IoT Smart Light Control System that automatically detects ambient light using an LDR sensor, controls an LED and buzzer based on light intensity, and uploads real-time monitoring data to the ThingSpeak Cloud via Wi-Fi.

OPERATION

The ESP32 continuously reads the ambient light intensity using an LDR sensor. The measured analog value is compared with a predefined threshold to determine whether the environment is Bright or Dark. When darkness is detected, the ESP32 automatically turns ON the LED and buzzer to indicate low-light conditions; otherwise, both remain OFF. Simultaneously, the current LDR value and light status are displayed on a 16×2 I2C LCD. Every 20 seconds, the ESP32 uploads the LDR reading and system status to the ThingSpeak IoT Cloud via Wi-Fi, enabling real-time remote monitoring and visualization of sensor data.
