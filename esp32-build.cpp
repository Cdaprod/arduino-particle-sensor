#include <Adafruit_Sensor.h>
#include <Adafruit_PM25AQI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>

#define OLED_RESET -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();
File dataFile;

void setup() {
  Serial.begin(115200);

  if (!SD.begin(5)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Dust Sensor Test");
  display.display();
  delay(2000);

  if (! aqi.begin_I2C()) {
    Serial.println("Could not find a valid PM25 sensor, check wiring!");
    while (1);
  }

  Serial.println("Dust Sensor and Display initialized!");
}

void loop() {
  uint16_t aqiValue = 0;

  if (! aqi.read(&aqiValue)) {
    Serial.println("Could not read from AQI sensor!");
    return;
  }

  Serial.print("PM 2.5: ");
  Serial.print(aqiValue);
  Serial.println(" ug/m3");

  dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("PM 2.5: ");
    dataFile.print(aqiValue);
    dataFile.println(" ug/m3");
    dataFile.close();
    Serial.println("Data saved to SD card!");
  }
  else {
    Serial.println("Error opening data.txt!");
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("PM 2.5: ");
  display.print(aqiValue);
  display.println(" ug/m3");
  display.display();

  delay(5000);
}
