//Plants.a.lot
#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>
WebServer Server;
AutoConnect Portal(Server);
#include <FastLED.h>//LED Ring
#include <DHT.h>;//humidity
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
//lux
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
#define TSL_SDA 23
#define TSL_SCL 19
//LED
#define DATA_PIN 17
#define NUM_LEDS 12
//
#define AUDIO_PIN 5
#define SOIL_PIN 34
//DHT22
#define DHTPIN 18
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
// Array of led data
CRGB leds[NUM_LEDS];
//sensorStates
bool luxFlag = false;
bool humFlag = false;
bool soilFlag = false;
bool audioFlag = false;

void sendPage() {
  if(luxFlag) {
    Server.sendHeader("Location","https://plantsalot.netlify.app/dark"); 
    Server.send(303);
  } else if(humFlag || soilFlag) {
    Server.sendHeader("Location","https://plantsalot.netlify.app/dry"); 
    Server.send(303);
  } else {
    Server.sendHeader("Location","https://plantsalot.netlify.app/safe"); 
    Server.send(303);
  }
}

void configureLux() {
  tsl.begin();
  tsl.setGain(TSL2591_GAIN_MED);
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  tsl2591Gain_t gain = tsl.getGain();
}

void playAudio() {
  digitalWrite(AUDIO_PIN, HIGH);
  digitalWrite(AUDIO_PIN, LOW);
}
void changeCheck() {
  if(luxFlag || humFlag || soilFlag) {
    if(audioFlag == false) {
      audioFlag = true;
      playAudio();
    }
    light(true);
  } else {
    audioFlag = false;
    light(false);
  }
}
void light(bool x)
{
  FastLED.clear();
  if (x == true) {
    for(int led=0; led<NUM_LEDS; led++)
    {
      leds[led] = CRGB::Green;
    }
  } else {
    FastLED.clear();
  }
  FastLED.show();
}

void setup() 
{
  delay(1000);
  Wire.begin(TSL_SDA, TSL_SCL);
  Server.on("/", sendPage);
  dht.begin();
  pinMode(SOIL_PIN, INPUT);
  pinMode(AUDIO_PIN, OUTPUT);
  configureLux();
  FastLED.setBrightness(80);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  if (Portal.begin()) {
    Serial.println("HTTP server:" + WiFi.localIP().toString());
  }
}

void luxCheck() {
  int x = tsl.getLuminosity(TSL2591_VISIBLE);
  if (x< 1100) {
    luxFlag = true;
  } else {
    luxFlag = false;
  }
}
void humCheck() {
  int hum = dht.readHumidity();
  if (hum < 40) {
    humFlag = true;
  } else {
    humFlag = false;
  }
}
void soilCheck() {
  int sensorValue = analogRead(SOIL_PIN);
  if (analogRead(SOIL_PIN)>2500) {
    soilFlag = true;
  } else {
    soilFlag = false;
  }
}

void loop() {
  EVERY_N_MILLIS(700) luxCheck();
  EVERY_N_MILLIS(1100) humCheck();
  EVERY_N_MILLIS(1300) soilCheck();
  EVERY_N_MILLIS(1000) changeCheck();
  Portal.handleClient();
}
