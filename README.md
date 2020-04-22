# Extend Wifi Range With ESP8266 (NodeMCU)
This project goal is extending WiFi range with ESP8266.
  Currently It is only supports IPv4 .

# Configuration
This system is requires Two way Configuration.
One of them is your router other one is ESP8266 (NodeMCU).

## ESP8266 Side

- Set your Home router WiFi SSID and password
```c++
const char* ssid     = "Dijitaller.com";
const char* password = "MyhomeNetworkPass";
```
- Set your ESP Wifi name, password and channel
```c++
const char* ssid_soft_ap     = "ahmetozer.org2";
const char* password_soft_ap = password;
int Wifi_SoftAP_Channel      = 11;
```

- Set your sub local network on ESP8266
.**Note:** Each ESP use /29 block but requires /24 block.
```c++
IPAddress local_IP(10,0,1,1);
IPAddress gateway(10,0,1,1);
IPAddress subnet(255,255,255,0);
```

- Set Your ESP8266 hostname.
```c++
const char* espHostname =     "WifiReperater2";
```

## Home Side
Firstly compile and flash firmware to your NodeMCU.  
Bootup your ESP8266.
Find ESP8266 IPAddress on your router.
Go to Advanced Routing settings


# Performance Tunings
- Change channel 9,10 or 11 on your Router.
- Select Same Wifi channel on your ESP8266.
it is delegated with `Wifi_SoftAP_Channel` variable.
- Increase CPU speed to 160 MHz to gain between 1.5 - 1.8 more speed on your extend project. You can found this setting on Arduino software under tools menu.
- Change lwIP library version to "V2 IPv6 High Bandwidth"
