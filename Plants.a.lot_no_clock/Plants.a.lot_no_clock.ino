//Plants.a.lot
#include <FastLED.h>//LED Ring
#include <DHT.h>;//humidity
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"//lux

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);//lux

#define TSL_SDA 23;
#define TSL_SCL 19;

// Common naming from FastLED demos
#define DATA_PIN 17
#define NUM_LEDS 12//light

#define AUDIO_PIN 5
#define SOIL_PIN 34

#define DHTPIN 18 //dht
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


// How many pulses per minute
uint8_t bpm = 30;

//dht22
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value


// Array of led data
CRGB leds[NUM_LEDS];

void light (bool x)
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

void configureLux() {
  Serial.println("wut?");
  if(tsl.begin()) {
    Serial.println("tsl found");
  } else {
    Serial.println("nope");
  }
  tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  tsl2591Gain_t gain = tsl.getGain();
}

void setup() 
{ 
  Serial.begin(9600);
  Wire.begin(TSL_SDA, TSL_SCL);
  delay(100);
  dht.begin();
  //soil
  pinMode(SOIL_PIN, INPUT);
  //lux
  configureLux();
   
   FastLED.setBrightness(80);
   FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
   FastLED.clear();
}

void loop() {
  EVERY_N_MILLIS(700) 
  {
    uint16_t x = tsl.getLuminosity(TSL2591_VISIBLE);
    if (x< 1100)
    {
      light(true);
      Serial.print("Lux: ");
      Serial.println(x);
      Serial.println(" -----------------");
    }

    else
    {
      light(false);
      Serial.println("Light OK");
    }
  }
  
  EVERY_N_MILLIS(1100) 
  {
    hum = dht.readHumidity();
    temp= dht.readTemperature();
  
    if (hum < 40)
    {
      light (true);
      Serial.print("Humidity: ");
      Serial.print(hum);
      Serial.println(" %");
      Serial.println(" -----------------");
      Serial.print("Temp: ");
      Serial.print(temp);
      Serial.println(" Celsius");
      Serial.println(" -----------------");
    }
    else
    {
      light(false);
      Serial.println("Hum OK");
    }
  }
   
  EVERY_N_MILLIS(1300) 
  {
    int sensorValue = analogRead(SOIL_PIN);
    if (analogRead(SOIL_PIN)>2500)
    {
      light (true);
      Serial.print("Humidity Soil: ");
      Serial.println(analogRead(SOIL_PIN));
      Serial.println(" -----------------");
    }
    else
    {
      light(false);
      Serial.println("Soil OK");
    }
  }
}
