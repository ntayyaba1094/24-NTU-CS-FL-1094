//Tayyaba_1094
//static IP
#include <WiFi.h>

const char* ssid     = "Tayyaba's A07"; 
const char* password = "yougotthis1910";           

// Static IP configuration 
IPAddress local_IP(10, 13, 37, 50);   // Desired fixed IP (e.g., 192.168.1.184 for home routers)
IPAddress gateway(10, 13, 37, 1);     // Router's IP address (e.g., 192.168.1.1)
IPAddress subnet(255, 255, 255, 0);   // Subnet mask
IPAddress primaryDNS(8, 8, 8, 8);     // Optional: Google DNS

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

  // Step 2: Apply Static IP configuration BEFORE WiFi.begin()
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS)) {
    Serial.println("Static IP configuration failed!");
  }

  // Step 3: Connect to Wi-Fi
  Serial.printf("\nConnecting to %s with Static IP", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Step 4: Verify Static IP details
  Serial.println("\nConnected! Static IP Details:");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway:    ");
  Serial.println(WiFi.gatewayIP());
}

void loop() {
}