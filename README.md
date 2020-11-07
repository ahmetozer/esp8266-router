# Extend Wifi Range With ESP8266 (NodeMCU)

This project goal is extending WiFi range with ESP8266.
  Currently It is only supports IPv4 .

## Configuration

This system is requires Two way Configuration.
One of them is your router other one is ESP8266 (NodeMCU).

### ESP8266 Side

- Set your Home router WiFi SSID and password

```c++
const char* SSID     = "ahmetozer.org";
const char* PASSWORD = "MyhomeNetworkPass";
```

- Set your ESP Wifi name, password and channel

```c++
const char* SOFT_AP_SSID     = "ahmet.engineer";
const char* SOFT_AP_PASSWORD = password;
int Wifi_SoftAP_Channel      = 11;
```

- Set your sub local network on ESP8266
.**Note:** Each ESP use /29 block but requires /24 block.

```c++
IPAddress SOFT_AP_Local_IP(10,0,1,1);
IPAddress SOFT_AP_Gateway(10,0,1,1);
IPAddress SOFT_AP_Subnet(255,255,255,0);
```

### Home Side

1. Firstly compile and flash firmware to your NodeMCU.  
2. Bootup your ESP8266.  
3. Find ESP8266 IPAddress on your router.  
4. Go to Advanced Routing settings.  
5. Add esp network to router.

<img src="https://github.com/ahmetozer/esp8266-router/blob/master/advanced_router_settings.jpg?raw=true" alt="Advanced route setting for ESP8266" onerror="this.src='advanced_router_settings.jpg';" />

## Performance Tunings

- Change channel 9,10 or 11 on your Router.
- Select Same Wifi channel on your ESP8266.
it is delegated with `Wifi_SoftAP_Channel` variable.
- Change lwIP library version to "V2 IPv6 High Bandwidth" or "V2 High Bandwidth".

## Without Configuring Home Side - Update

Nat is Disabled by default for better performance but if you don't have chance to edit route table on router or having issue, you can enable NAT on ESP8266.
**NOTE: You have to select lwIP library version to "V2 High Bandwidth" for enabling nat. Other wise nat will not work.

## [Source Code - Github](https://github.com/ahmetozer/esp8266-router) | [BLOG](https://ahmetozer.org/ESP8266-Wifi-Range-Extender.html)
