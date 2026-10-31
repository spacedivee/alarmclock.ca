#include <Adafruit_GFX.h>      
#include <Adafruit_ST7789.h>  
#include <SPI.h>              
#include <ESP32Time.h>        
#include <WiFi.h>
#include "time.h"


#define TFT_SCLK 8   // D8 (Hardware SCK)
#define TFT_MOSI 10  // D10 (Hardware MOSI)
#define TFT_CS   7   // D7
#define TFT_DC   4   // D2 (Safe layout move)
#define TFT_RST  3   // D1 (Safe layout move)
#define TFT_BL   2   // D0 

#define ALARM_BUTTON 20 // D4
#define PIEZO_BUZZER 21 // D5


const char* ssid     = "i would include my ssid but not rn";
const char* password = "not putting it buddy";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000; 
const int   daylightOffset_sec = 3600; 

class MyST7789 : public Adafruit_ST7789 {
public:
  MyST7789(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk, int8_t rst)
    : Adafruit_ST7789(cs, dc, mosi, sclk, rst) {}
    
  void setOffsets(uint8_t col, uint8_t row) {
    _colstart = _colstart2 = col;
    _rowstart = _rowstart2 = row;
  }
};

MyST7789 tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
ESP32Time rtc;

int alarmHour = 7;   
int alarmMinute = 30;
bool isAlarmTriggered = false;
bool alarmCheckedThisMinute = false; 
String lastDisplayedTime = "";

void setup() {
  Serial.begin(115200);

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, LOW); // Turn screen backlight ON
  
  pinMode(ALARM_BUTTON, INPUT_PULLUP);
  pinMode(PIEZO_BUZZER, OUTPUT);
  digitalWrite(PIEZO_BUZZER, LOW);

  // Screen Initialization
  tft.init(76, 284);
  tft.setOffsets(82, 18);
  tft.invertDisplay(false);
  tft.setRotation(1); 
  tft.fillScreen(ST77XX_BLACK);


  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 15) { // 7.5 second timeout limit
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected! Syncing Time...");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
      rtc.setTimeStruct(timeinfo); // Sync internal RTC to internet time!
      Serial.println("Time successfully synchronized via NTP.");
    }
    WiFi.disconnect(true); // Shut off Wi-Fi radio to save power/reduce heat
    WiFi.mode(WIFI_OFF);
  } else {
    Serial.println("\nWi-Fi failed. Falling back to hardcoded manual time.");
    // Manual fallback if Wi-Fi isn't found
    rtc.setTime(30, 29, 7, 29, 10, 2026); 
  }

  Serial.println("Blare StarDance Clock Initialized!");
}

void loop() {
  int currentHour = rtc.getHour(true); 
  int currentMinute = rtc.getMinute();
  String timeString = rtc.getTime("%H:%M:%S");

  // Display Refresh Optimization
  if (timeString != lastDisplayedTime) {
    tft.setTextSize(4);
    tft.setCursor(15, 22);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK); 
    tft.print(timeString);
    lastDisplayedTime = timeString;
  }

  // Alarm Logic Check
  if (currentHour == alarmHour && currentMinute == alarmMinute) {
    if (!alarmCheckedThisMinute) {
      isAlarmTriggered = true;
      alarmCheckedThisMinute = true;
      Serial.println("ALARM TRIGGERED!");
    }
  } else {
    alarmCheckedThisMinute = false; 
  }

  // Handle Active Alarm State
  if (isAlarmTriggered) {
    digitalWrite(TFT_BL, (millis() / 200) % 2); 
    digitalWrite(PIEZO_BUZZER, (millis() / 100) % 2);

    if (digitalRead(ALARM_BUTTON) == LOW) {
      isAlarmTriggered = false;
      digitalWrite(PIEZO_BUZZER, LOW);
      digitalWrite(TFT_BL, LOW); 
      Serial.println("Alarm silenced by user.");
      delay(1000); 
    }
  }

  delay(50); 
}
