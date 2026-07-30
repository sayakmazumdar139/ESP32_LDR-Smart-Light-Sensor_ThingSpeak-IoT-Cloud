#include <WiFi.h>
#include "ThingSpeak.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LDR_PIN 34
#define LED_PIN 26
#define BUZZER_PIN 27

LiquidCrystal_I2C lcd(0x27,16,2);

int threshold = 1800;

const char* ssid = "TP-Link_D848";
const char* password = "13185787";

// Replace with your own values
unsigned long channelID = 3435716;
const char* writeAPIKey = "HG84U0XIP5K60TU8";

WiFiClient client;

unsigned long lastUpload = 0;

void setup()
{
  Serial.begin(115200);

  pinMode(LED_PIN,OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Smart Light");
  lcd.setCursor(0,1);
  lcd.print("Monitoring");

  delay(2000);
  lcd.clear();

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

  ThingSpeak.begin(client);
}

void loop()
{
  int ldrValue = analogRead(LDR_PIN);
  int lightStatus;

  Serial.print("LDR Value : ");
  Serial.println(ldrValue);

  lcd.clear();

  if(ldrValue > threshold)
  {
      digitalWrite(LED_PIN,HIGH);
      digitalWrite(BUZZER_PIN,HIGH);

      lightStatus = 1;      // Dark

      lcd.setCursor(0,0);
      lcd.print("ROOM DARK");

      lcd.setCursor(0,1);
      lcd.print("LED ON");

      Serial.println("Dark Detected");
  }
  else
  {
      digitalWrite(LED_PIN,LOW);
      digitalWrite(BUZZER_PIN,LOW);

      lightStatus = 0;      // Bright


      lcd.setCursor(0,0);
      lcd.print("ROOM BRIGHT");

      lcd.setCursor(0,1);
      lcd.print("LED OFF");

      Serial.println("Bright");
  }

  if (millis() - lastUpload > 20000)
{
    ThingSpeak.setField(1, ldrValue);
    ThingSpeak.setField(2, lightStatus);

    int response = ThingSpeak.writeFields(channelID, writeAPIKey);

    if(response == 200)
    {
        Serial.println("LDR uploaded successfully.");
    }
    else
    {
        Serial.print("ThingSpeak Error : ");
        Serial.println(response);
    }

    lastUpload = millis();
}
 delay(500);
}