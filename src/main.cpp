#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WiFi.h>
#include <WiFiGeneric.h>
#include <Ticker.h>

#define SCREEN_WIDTH 128 // OLED width,  in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels
#define DHT11_PIN 23

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht11(DHT11_PIN, DHT11);

void setupOled()
{
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1)
      ;
  }

  oled.clearDisplay(); // clear display
  oled.setCursor(0, 20);
  oled.setTextSize(1);
  oled.setTextColor(WHITE, BLACK);
}

void setup()
{
  Serial.begin(115200);

  setupOled();
  dht11.begin();

  // init
  delay(2000);
}

void loop()
{
  oled.clearDisplay();
  oled.setCursor(0, 20);

  float tempC = dht11.readTemperature();
  float humi = dht11.readHumidity();

  oled.printf("T=%.1f°C\nH=%.1f", tempC, humi);
  oled.display();

  delay(2000);
}