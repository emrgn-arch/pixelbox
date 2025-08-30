#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#include "web_page.h"

// LEFT-to-RIGHT 3V3 GND D2 D0 D1 D7 D5

// === TFT Display Pins ===
#define TFT_RST   16
#define TFT_CS    4
#define TFT_DC    5
#define RESET_WiFi D6
#define LED_SIGNAL D3

// === Virtual Grid Settings === Calculate this later
const int rows = 43;
const int cols = 43;
const int pixelSize = 3;

// === TFT Instance ===
Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

// === WiFi / EEPROM ===

WiFiManager wm;
ESP8266WebServer server(80);
char ssid[64], pass[64];
bool shouldSaveConfig = false;

// === Save credentials to EEPROM ===
void saveCredentials(const char* newSSID, const char* newPass) {
  for (int i = 0; i < 32; i++) {
    EEPROM.write(i, newSSID[i]);
    EEPROM.write(100 + i, newPass[i]);
  }
  EEPROM.commit();
}

// === Read credentials from EEPROM ===
void readCredentials() {
  for (int i = 0; i < 32; i++) {
    ssid[i] = EEPROM.read(i);
    pass[i] = EEPROM.read(100 + i);
  }
  ssid[31] = '\0';
  pass[31] = '\0';
}

// === Save config callback ===
void saveConfigCallback() {
  shouldSaveConfig = true;
}

// === Draw 1 grid block ===
void drawPixelBlock(int x, int y, uint16_t color) {
  tft.fillRect(x * pixelSize, y * pixelSize, pixelSize, pixelSize, color);
}

// === Draw the grid lines ===
void drawGrid(int cellWidth, int cellHeight, int cols, int rows) {
  for (int y = 1; y < rows; y++)
    tft.drawFastHLine(0, y * cellHeight - 1, cols * cellWidth, ST77XX_BLACK);
  for (int x = 1; x < cols; x++)
    tft.drawFastVLine(x * cellWidth - 1, 0, rows * cellHeight, ST77XX_BLACK);
}

// === Reusable CORS headers ===
void setCORSHeaders() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "POST, OPTIONS, GET");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

// === Serve index.html from SPIFFS ===
void handleRoot() {
  setCORSHeaders();
  String html = MAIN_page;  // copy from PROGMEM into RAM
  html.replace("%%IP%%", WiFi.localIP().toString());
  server.send(200, "text/html", html);
}

// === Clear screen ===
void handleClear() {
  setCORSHeaders();
  //tft.fillScreen(ST77XX_BLACK);
  tft.fillScreen(((0x0D & 0xF8) << 8) | ((0x06 & 0xFC) << 3) | (0x02 >> 3));
  server.send(200, "text/plain", "Cleared");
}

// === Handle batch draw JSON ===
void handleBatchDraw() {
  setCORSHeaders();

  analogWrite(LED_SIGNAL, 20);

  if (!server.hasArg("plain")) {
    server.send(400, "text/plain", "Missing JSON payload");
    return;
  }

  const size_t capacity = JSON_ARRAY_SIZE(320) + 320 * JSON_OBJECT_SIZE(5);
  DynamicJsonDocument doc(capacity);

  DeserializationError error = deserializeJson(doc, server.arg("plain"));
  if (error) {
    server.send(400, "text/plain", "JSON parse error");
    return;
  }

  for (JsonObject pixel : doc.as<JsonArray>()) {
    int x = pixel["x"];
    int y = pixel["y"];
    int r = pixel["r"];
    int g = pixel["g"];
    int b = pixel["b"];
    drawPixelBlock(x, y, tft.color565(r, g, b));
  }

  drawGrid(pixelSize, pixelSize, cols, rows);

  analogWrite(LED_SIGNAL, 0);

  server.send(200, "text/plain", "Batch Draw OK");
}

// === WiFi setup (with WiFiManager) ===
void setupWiFi() {
  EEPROM.begin(512);
  pinMode(RESET_WiFi, INPUT_PULLUP);  // Config button

  wm.setSaveConfigCallback(saveConfigCallback);

  if (digitalRead(RESET_WiFi) == LOW) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
    tft.setCursor(0, 0);
    tft.print("Connect WiFi to MiniPC_Config");
    wm.startConfigPortal("MiniPC_Config");
    if (shouldSaveConfig) {
      saveCredentials(wm.getWiFiSSID().c_str(), wm.getWiFiPass().c_str());
      ESP.restart();
    }
  } else {
    readCredentials();
    WiFi.begin(ssid, pass);
    unsigned long startAttempt = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 10000) {
      delay(500);
      Serial.print(".");
    }

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("\nFailed to connect, starting config portal...");

      tft.fillScreen(ST77XX_BLACK);
      tft.setTextColor(ST77XX_WHITE);
      tft.setTextSize(1);
      tft.setCursor(0, 0);
      tft.print("Connect WiFi to MiniPC_Config");
      wm.startConfigPortal("MiniPC_Config");     
    
      if (shouldSaveConfig) {
        saveCredentials(wm.getWiFiSSID().c_str(), wm.getWiFiPass().c_str());
        ESP.restart();
      }
    }
  }

  Serial.println("\nWiFi connected: " + WiFi.localIP().toString());

  // Show IP on TFT for 3 seconds
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.print("IP Address:");
  tft.setCursor(0, 11);
  tft.print(WiFi.localIP().toString());
  delay(3000); 
  tft.fillScreen(ST77XX_BLACK);
}

// === Setup TFT and SPIFFS ===
void setupTFTAndSPIFFS() {
  tft.initR(INITR_144GREENTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  drawGrid(pixelSize, pixelSize, cols, rows);
  
}

// === Setup routes ===
void setupWebServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/clear", HTTP_GET, handleClear);

  server.on("/batchDraw", HTTP_OPTIONS, []() {
    setCORSHeaders();
    server.send(204);
  });

  server.on("/batchDraw", HTTP_POST, handleBatchDraw);
  server.begin();
  Serial.println("HTTP server started");
}

void setup() {
  Serial.begin(115200);  
  setupTFTAndSPIFFS();
  setupWiFi();
  setupWebServer();
  pinMode(LED_SIGNAL, OUTPUT); 
}

void loop() {
  server.handleClient();             
}
