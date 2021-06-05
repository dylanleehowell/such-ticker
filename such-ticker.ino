// such-ticker: This sketch retrieves the dogecoin price via an HTTP client and writes it to an LCD.

#include <ArduinoJson.h>
#include <rgb_lcd.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char *ssid = "<your-ssid-here>";
const char *password = "<your-password-here>";

rgb_lcd lcd;
WiFiClientSecure wifiClient;
HTTPClient http;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long updatePeriod = 10000;
int color = 0;

void setup() {
  startMillis = millis();
  lcd.begin(16, 2);
  lcd.setRGB(0, 0, 255);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(10);
  wifiClient.setInsecure();
  http.useHTTP10(true);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  String ipAddress = WiFi.localIP().toString();
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: " + ipAddress);
  lcdPrint(ipAddress);
}

void loop() {
  currentMillis = millis();
  if (currentMillis - startMillis >= updatePeriod) {
    getData();
    startMillis = currentMillis;
  }
  bumpColor();
  delay(1000);
}

void getData() {
  String server = "https://sochain.com";
  wifiClient.connect(server, 443);
  http.begin(wifiClient, server + "/api/v2/get_price/DOGE/USD");
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Stream &response = http.getStream();
    DynamicJsonDocument doc(2048);
    deserializeJson(doc, response);
    JsonArray prices = doc["data"]["prices"];
    String price = "DOGE: " + prices[1]["price"].as<String>();
    Serial.println(price);
    lcdPrint(price);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  wifiClient.stop();
}

void lcdPrint(const String& text) {
  lcd.setCursor(0, 1);
  lcd.print(text);
}

void bumpColor() {
  if (color > 16777216) {
    color = 0;
  }
  int red   = (color >> 16) & 0xFF;
  int green = (color >> 8) & 0xFF;
  int blue  = (color) & 0xFF;
  lcd.setRGB(red, green, blue);
  color = color + 500;
}
