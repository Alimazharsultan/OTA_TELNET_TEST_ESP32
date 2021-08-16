#include <WiFi.h>
#include <WiFiClient.h>
#include "OTA.h"
#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks
#define EAP_IDENTITY "elt@austd.com" //if connecting from another corporation, use identity@organisation.domain in Eduroam 
#define EAP_PASSWORD "elt" //your Eduroam password
const char* ssid = "eduroam"; // Eduroam SSID
const char* host = "arduino.php5.sk"; //external server domain for HTTP connection after authentification
int counter=0;
void Setup_wifi(){
  Serial.print("Connecting to network: ");
  Serial.println(ssid);
  WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
  WiFi.mode(WIFI_STA); //init wifi mode
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide identity
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide username --> identity and username is same
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD)); //provide password
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); //set config settings to default
  esp_wifi_sta_wpa2_ent_enable(&config); //set config settings to enable function
  WiFi.begin(ssid); //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if(counter>=60){ //after 30 seconds timeout - reset board
      ESP.restart();
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address set: "); 
  Serial.println(WiFi.localIP()); //print LAN IP
  }
uint32_t entry;

void setup() {
  Serial.begin(115200);

  Setup_wifi();
  // put your setup code here, to run once:
}

void loop() {
ArduinoOTA.handle();
  TelnetStream.println(micros() - entry);
  TelnetStream.println("Loop1");
  TelnetStream.println("Hello From ESP");
  delay(1000);
}
