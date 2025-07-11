#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TEMP_PIN 36
#define VOLT_PIN 39
#define RED_PIN 18
#define GREEN_PIN 19
#define BLUE_PIN 23
#define BUZZER_PIN 5


const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String firebaseURL = "https://satellite-monitor-72be8-default-rtdb.europe-west1.firebasedatabase.app/data.json";

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  Serial.begin(115200);

  // Pin modes
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Satellite Health");
  display.display();
  delay(1000);

  // WiFi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  int rawT = analogRead(TEMP_PIN);
  int rawV = analogRead(VOLT_PIN);

  float temp = (rawT / 4095.0) * 50.0; // ESP32 uses 12-bit ADC (0–4095)
  float volt = (rawV / 4095.0) * 5.0;

  Serial.print("TEMP: ");
  Serial.print(temp, 2);
  Serial.print(" °C, VOLT: ");
  Serial.print(volt, 2);
  Serial.println(" V");

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temp, 1);
  display.println(" C");
  display.print("Volt: ");
  display.print(volt, 2);
  display.println(" V");

  String status;

  if (temp > 40.0) {
    status = "OVERHEAT";
    setColor(255, 0, 0);
    tone(BUZZER_PIN, 1000);
  } else if (volt < 3.3) {
    status = "LOW BAT";
    setColor(0, 0, 255);
    tone(BUZZER_PIN, 800);
  } else {
    status = "NORMAL";
    setColor(0, 255, 0);
    noTone(BUZZER_PIN);
  }

  display.println("Status: " + status);
  display.display();

  // Send data to Firebase
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://satellite-monitor-72be8-default-rtdb.europe-west1.firebasedatabase.app/history.json");

    http.addHeader("Content-Type", "application/json");

    String jsonData = "{\"temperature\":" + String(temp, 2) + 
                      ",\"voltage\":" + String(volt, 2) + 
                      ",\"status\":\"" + status + "\"}";

    int httpResponseCode = http.POST(jsonData);
    Serial.print("Firebase response: ");
    Serial.println(httpResponseCode);
    http.end();
  }

  delay(2000);
}

void setColor(int r, int g, int b) {
  digitalWrite(RED_PIN, r > 0 ? HIGH : LOW);
  digitalWrite(GREEN_PIN, g > 0 ? HIGH : LOW);
  digitalWrite(BLUE_PIN, b > 0 ? HIGH : LOW);
}
