//tayyaba's 
//dhcp


#include <WiFi.h>

const char* ssid     = "Tayyaba's A07"; 
const char* password = "yougotthis1910";            

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Step 1: Scan available networks
  Serial.println("Scanning Wi-Fi networks...");
  int n = WiFi.scanNetworks();
  Serial.printf("%d networks found:\n", n);

  for (int i = 0; i < n; ++i) {
    Serial.printf("%d: %s (%d dBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }
  WiFi.scanDelete();

  // Step 2: Connect via DHCP (automatic IP assignment)
  Serial.printf("\nConnecting to %s via DHCP", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Step 3: Print DHCP-assigned network details
  Serial.println("\nConnected! DHCP IP Details:");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway:    ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Subnet:     ");
  Serial.println(WiFi.subnetMask());
}

void loop() {
  // Nothing needed here for a one-time scan + DHCP connect
}
