#include <ESP8266WiFi.h>

// Write Your Router SSID which is your wifi name and your wifi password.
const char* ssid     = "Dijitaller.com";
const char* password = "MyhomeNetworkPass";

// Your ESP Wifi
const char* ssid_soft_ap     = "ahmetozer.org2";
const char* password_soft_ap = password;          // My preference is same as my home ssid password.
int Wifi_SoftAP_Channel      = 11;

// ESP 8266 Local Network Configuration
IPAddress local_IP(10,0,1,1);
IPAddress gateway(10,0,1,1);
IPAddress subnet(255,255,255,0);

// Rename Your ESP name to find easily on your router
const char* espHostname =     "WifiReperater2";
   
void setup() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.hostname(espHostname);
    delay(500);
  }
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid_soft_ap, password_soft_ap, Wifi_SoftAP_Channel);
}

void loop() {
}
