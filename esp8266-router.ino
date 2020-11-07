#include <ESP8266WiFi.h>

#include <lwip/dns.h>
#include <dhcpserver.h>

#if LWIP_FEATURES

#define SERIAL_DEBUG true // To show details on serial
// Write Your Router SSID which is your wifi name and your wifi PASSWORD.
const char *SSID = "ahmetozer.org";
const char *PASSWORD = "12345678";

// Your ESP Wifi
const char *SOFT_AP_SSID = "ahmet.engineer";
const char *SOFT_AP_PASSWORD = PASSWORD; // My preference is same as my home SSID PASSWORD.
int SOFT_AP_Channel = 11;

// ESP 8266 Local Network Configuration
IPAddress SOFT_AP_Local_IP(10, 0, 1, 1);
IPAddress SOFT_AP_Gateway(10, 0, 1, 1);
IPAddress SOFT_AP_Subnet(255, 255, 255, 0);
#define Copy_DNS_Settings true // if this is set to true
// System copy connected modem dns settings to dns server, other wise set to Cloudflare Public DNS
IPAddress SOFT_AP_DNS1(1, 1, 1, 1);
IPAddress SOFT_AP_DNS2(1, 0, 0, 1);

// Rename Your ESP name to find easily on your router
const char *espHostname = SOFT_AP_SSID; // By default, hostname is AP SSID but if you want you can set by manual by replace SOFT_AP_SSID with "YourHostName";

#define NAT_Enabled false

#if NAT_Enabled  && !LWIP_IPV6
#define NAPT 1000
#define NAPT_PORT 10
#include <lwip/napt.h>
#endif

void setup()
{
#if SERIAL_DEBUG
  Serial.begin(115200);
  Serial.println();
  Serial.println("\n\n\nStarting ...");
#endif
  WiFi.mode(WIFI_AP_STA);
#if SERIAL_DEBUG
  Serial.print("Connecting to ");
  Serial.println(SSID);
#endif
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
#if SERIAL_DEBUG
    Serial.print(".");
#endif
    delay(500);
  }
  WiFi.hostname(espHostname);
#if Copy_DNS_Settings
  SOFT_AP_DNS1 = WiFi.dnsIP(0);
  SOFT_AP_DNS2 = WiFi.dnsIP(1);
#endif

  dhcps_set_dns(0, SOFT_AP_DNS1);
  dhcps_set_dns(1, SOFT_AP_DNS2);

  WiFi.softAPConfig(SOFT_AP_Local_IP, SOFT_AP_Gateway, SOFT_AP_Subnet);
  WiFi.softAP(SOFT_AP_SSID, SOFT_AP_PASSWORD, SOFT_AP_Channel);
#if SERIAL_DEBUG
  // Wifi Client Part
  Serial.printf("\nConnected WiFi %s\n MAC addr: %s\nESP8266 client ip address: %s \nDNS adresses: %s , %s\n",
  SSID, WiFi.softAPmacAddress().c_str(),
  WiFi.localIP().toString().c_str(),
  WiFi.dnsIP(0).toString().c_str(),
  WiFi.dnsIP(1).toString().c_str());
  // Wifi AP Part
  Serial.printf("Ap Info\nEsp AP IPAddress: %s \nDHCP Settings\nGateway: %s \nSubnet: %s\nDNS: %s - %s\n",
  WiFi.softAPIP().toString().c_str(),
  SOFT_AP_Gateway.toString().c_str(),
  SOFT_AP_Subnet.toString().c_str(),
  SOFT_AP_DNS1.toString().c_str(),SOFT_AP_DNS2.toString().c_str());

#endif

#if NAT_Enabled  && !LWIP_IPV6
  err_t nat_err = ip_napt_init(NAPT, NAPT_PORT);
#if SERIAL_DEBUG
  Serial.println("Initializing NAT");
#endif
  if (nat_err == ERR_OK)
  {
    nat_err = ip_napt_enable_no(SOFTAP_IF, 1);
#if SERIAL_DEBUG
    Serial.println("Enabling NAT on AP");
#endif
    if (nat_err == ERR_OK)
    {
#if SERIAL_DEBUG
      Serial.printf("Nat Is Enabled on '%s' \n", SOFT_AP_SSID);
#endif
    }
  }

  if (nat_err != ERR_OK)
  {
#if SERIAL_DEBUG
    Serial.println("ERR: NAT is not initialized");
#endif
  }
#elif NAT_Enabled
    Serial.println("ERR: NAT is not initialized");
    Serial.println("\n\n\nPlease select LwIP Variant: v2 Higher Bandwidth or v2 Lower Memory");
#endif
}

#else
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("\n\n\nPlease select LwIP Variant: v2 Higher Bandwidth or v2 Lower Memory");
}
#endif

void loop()
{
}
