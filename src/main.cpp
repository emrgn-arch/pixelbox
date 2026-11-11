#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <qrcode.h>

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

#define AP_NAME "MiniPC_Config"

WiFiManager wm;
ESP8266WebServer server(80);
char ssid[64], pass[64];
bool shouldSaveConfig = false;
bool qrOnScreen = false;  // browser QR stays up until the device is first used

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

// === QR code screens ===
// How many bytes fit in QR versions 1-6 (low error correction, byte mode)
const uint8_t QR_CAPACITY[] = {17, 32, 53, 78, 106, 134};

void printCentered(const String& text, int y) {
  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(text, 0, y, &x1, &y1, &w, &h);
  tft.setCursor((tft.width() - w) / 2, y);
  tft.print(text);
}

// Full-screen QR with a title above it and one or two text lines below it
void showQRScreen(const String& title, const String& payload, const String& line1, const String& line2 = "") {
  uint8_t version = 1;
  while (version < sizeof(QR_CAPACITY) && payload.length() > QR_CAPACITY[version - 1]) version++;
  if (payload.length() > QR_CAPACITY[version - 1]) {
    Serial.println("QR payload too long: " + payload);
    return;
  }

  QRCode qr;
  uint8_t qrData[qrcode_getBufferSize(version)];
  qrcode_initText(&qr, qrData, version, ECC_LOW, payload.c_str());

  // Fit the code between the title and footer, keeping a white border of 2 modules
  const int lineH = 10, margin = 4, border = 2;
  int areaTop = margin + lineH;
  int areaBottom = tft.height() - margin - (line2.length() ? 2 : 1) * lineH;
  int areaH = areaBottom - areaTop;
  int scale = max(1, min(areaH, (int)tft.width()) / (qr.size + 2 * border));
  int qrPx = qr.size * scale;
  int x0 = (tft.width() - qrPx) / 2;
  int y0 = areaTop + (areaH - qrPx) / 2;

  tft.fillScreen(ST77XX_WHITE);
  for (uint8_t y = 0; y < qr.size; y++)
    for (uint8_t x = 0; x < qr.size; x++)
      if (qrcode_getModule(&qr, x, y))
        tft.fillRect(x0 + x * scale, y0 + y * scale, scale, scale, ST77XX_BLACK);

  tft.setTextColor(ST77XX_BLACK);
  tft.setTextSize(1);
  printCentered(title, margin);
  printCentered(line1, areaBottom);
  if (line2.length()) printCentered(line2, areaBottom + lineH);
}

// Escape characters that have meaning in a WIFI: QR payload
String escapeWiFiField(const String& s) {
  String out;
  for (char c : s) {
    if (strchr("\\;,:\"", c)) out += '\\';
    out += c;
  }
  return out;
}

// Called by WiFiManager once the setup hotspot is up; stays on screen while the portal runs
void showWiFiSetupQR(WiFiManager* m) {
  String apName = m->getConfigPortalSSID();
  showQRScreen("Scan to set up WiFi",
               "WIFI:T:nopass;S:" + escapeWiFiField(apName) + ";;",
               "Join: " + apName,
               "Then: " + WiFi.softAPIP().toString());
}

// QR that opens the drawing page; stays up until the page is opened or something is drawn
void showBrowserQR() {
  String ip = WiFi.localIP().toString();
  showQRScreen("Scan to draw", "http://" + ip + "/", ip);
  qrOnScreen = true;
}

void hideQR() {
  if (!qrOnScreen) return;
  qrOnScreen = false;
  tft.fillScreen(ST77XX_BLACK);
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
  hideQR();
  String html = MAIN_page;  // copy from PROGMEM into RAM
  html.replace("%%IP%%", WiFi.localIP().toString());
  server.send(200, "text/html", html);
}

// === Clear screen ===
void handleClear() {
  setCORSHeaders();
  qrOnScreen = false;
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

  hideQR();
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

// === Config portal (blocks until WiFi is set up; QR is drawn by showWiFiSetupQR) ===
void runConfigPortal() {
  wm.startConfigPortal(AP_NAME);
  if (shouldSaveConfig) {
    saveCredentials(wm.getWiFiSSID().c_str(), wm.getWiFiPass().c_str());
    ESP.restart();
  }
}

// === WiFi setup (with WiFiManager) ===
void setupWiFi() {
  EEPROM.begin(512);
  pinMode(RESET_WiFi, INPUT_PULLUP);  // Config button

  wm.setSaveConfigCallback(saveConfigCallback);
  wm.setAPCallback(showWiFiSetupQR);

  if (digitalRead(RESET_WiFi) == LOW) {
    runConfigPortal();
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
      runConfigPortal();
    }
  }

  // Portal was exited without saving: retry with the stored credentials
  if (WiFi.status() != WL_CONNECTED) ESP.restart();

  Serial.println("\nWiFi connected: " + WiFi.localIP().toString());
  showBrowserQR();
}

// === Pressing the config button while running shows the browser QR again ===
void checkButton() {
  static bool wasPressed = false;
  static unsigned long lastPress = 0;
  bool pressed = digitalRead(RESET_WiFi) == LOW;
  if (pressed && !wasPressed && millis() - lastPress > 300) {
    lastPress = millis();
    showBrowserQR();
  }
  wasPressed = pressed;
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
  checkButton();
}
