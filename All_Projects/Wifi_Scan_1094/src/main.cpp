#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);   // ESP32 ko client/station mode mein set karein
  WiFi.disconnect();     // Kisi purane network se disconnect karein
  delay(100);
}

void loop() {
  int n = WiFi.scanNetworks(); // Aas-paas ke networks scan karein
  Serial.printf("%d networks found\n", n);

  for (int i = 0; i < n; ++i) {
    Serial.printf("%d: %s (%d dBm) Ch %d %s\n",
                  i + 1,
                  WiFi.SSID(i).c_str(),     // Wi-Fi ka naam
                  WiFi.RSSI(i),             // Signal strength
                  WiFi.channel(i),          // Channel number
                  (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "[Open]" : "[Secured]");
  }

  WiFi.scanDelete(); // Memory saaf karein
  delay(5000);       // 5 second baad dobara scan karein
}
