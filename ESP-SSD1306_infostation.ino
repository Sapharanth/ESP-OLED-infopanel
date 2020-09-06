#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include "SSD1306Wire.h"   
#include "crest.h" // comment out if you don't want/have a splash image

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
SSD1306Wire display(0x3c, 0, 2);  // ADDRESS, SDA, SCL  -  If not, they can be specified manually. Here, GPIO00 goes to screen's SDA, GPIO02 to SCK.

#define WIFI_SSID "Your Wi-Fi SSID"
#define WIFI_PASSWORD "Your Wi-Fi password"
// Raspberri Pi Mosquitto MQTT Broker
#define MQTT_HOST IPAddress(0, 0, 0, 0) // input IP address of your broker in this format
#define MQTT_PORT 1883
#define MQTT_READTOPIC "" // Topic on which JSON input is sent
#define MQTT_PUBLISHTOPIC "" // Topic on which to call for updates

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long previousMillis = 0;   // Stores last time temperature was published
const long interval = 30000;        // Interval at which to publish sensor readings

void setup() 
{
  // initialize screen
  display.init();
  display.flipScreenVertically();
  displaySplash(); // display boot screen bitmap from crest.h
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    yield();
  }

  // connect to MQQT, set callback
  client.setServer(MQTT_HOST, MQTT_PORT);
  client.setCallback(callback);
  while (!client.connected()) {

    if (!client.connect("ESP32Client"))
    {
      delay(500);
    }
  } 
  requestMQQT(); // comment this and uncomment line below to receive data that gets set periodically (Node-RED time inject, for example)
  //client.subscribe(MQTT_READTOPIC);
}


void callback(char* topic, byte* payload, unsigned int length) 
{
  String json = (char*)payload;  //forgot to test if it works fine if you pass just the char*
  JSONPrint(json);
  return;
}

void displaySplash()
{
  display.clear();
  //display.invertDisplay(); // i made a mistake when creating the file, necessiting this method
  display.drawXbm(0, 0, crest_width, crest_height, crest_bits);
  display.display();
  return;
}

void JSONPrint(String json)
{
  const size_t capacity = 7*JSON_ARRAY_SIZE(2) + JSON_ARRAY_SIZE(8) + 160;
  DynamicJsonDocument doc(capacity);
  DeserializationError error = deserializeJson(doc, json);

  const char* label1 = doc[0][0]; // "Key 1"
  const char* value1 = doc[0][1]; // "Value 1"

  const char* label2 = doc[1][0]; // "Key 2"
  const char* value2 = doc[1][1]; // "Value 2"

  const char* label3 = doc[2][0]; // "Key 3"
  const char* value3 = doc[2][1]; // "Value 3"

  const char* label4 = doc[3][0]; // "Key 4"
  const char* value4 = doc[3][1]; // "Value 4"

  const char* label5 = doc[4][0]; // "Key 5"
  const char* value5 = doc[4][1]; // "Value 5"

  const char* label6 = doc[5][0]; // "Key 6"
  const char* value6 = doc[5][1]; // "Value 6"

  const char* label7 = doc[6][0]; // "Key 7"
  const char* value7 = doc[6][1]; // "Value 7"
  
  int pos = doc[7]; // 50

  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10); 
  
  // Here's the heart. First variable is vertical position, second is position passed from JSON, third and fourth are key-value pairs.
  printLine(0, pos, label1, value1);
  printLine(1, pos, label2, value2);
  printLine(2, pos, label3, value3);
  printLine(3, pos, label4, value4);
  printLine(4, pos, label5, value5); 
  printLine(5, pos, label6, value6);
  printLine(6, pos, label7, value7);

  display.display();
  return;
}

void printLine(unsigned int position, int lineposition, const char* leftline, const char* rightline)
{
    // prints key-value pairs, works with ArialMT_Plain_10 as font. Changing sizes will require changing the position multiplier
    display.drawString(0, position*9, leftline);
    display.drawString(lineposition, position*9, rightline);
    return;
}

void requestMQQT() 
{
    // fire and forget. Node-RED is set up to send a JSON string after receiving a ping
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      char pingmsg[] = "Ping!";
      // Once connected, publish an announcement...
      client.publish(MQTT_PUBLISHTOPIC, pingmsg);
      // ... and resubscribe
      client.subscribe(MQTT_READTOPIC);
    } else {
      // Wait 5 seconds before retrying
      delay(5000);
    }
}

void loop(void) 
{ 
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) // resends a query every 30 seconds, in case you want to leave it on for some time
  {
  previousMillis = currentMillis;
  requestMQQT();
  }
  client.loop();
}