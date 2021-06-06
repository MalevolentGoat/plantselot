//Plants.a.lot
#include <FastLED.h>//LED Ring
#include <DHT.h>;//humidity
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"//lux

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);//lux

// Common naming from FastLED demos
#define DATA_PIN 17
#define NUM_LEDS 12//light

#define DHTPIN 18 
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
    
//  EVERY_N_MILLIS(2) 
//    {
//      // Clear strip
//        FastLED.clear();
//      
//        // beat8(x) returns a number from 0 to 255, looping x times per minute
//        uint8_t pos = beat8(bpm); 
//
//        // Convert the position to an index for the LED on our strip
//        uint8_t led = map8(pos,0,NUM_LEDS-1);
//        leds[led] = CRGB::Green;
//        FastLED.show();
//    }
      FastLED.clear();
      if (x == true){
  
      for(int led=0; led<NUM_LEDS; led++)
      {
      leds[led] = CRGB::Green;
      }
      FastLED.show();
      }

      else if (x == false){
        FastLED.clear();
      }
}

//lux
void configureSensor(void)
{
  tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  tsl2591Gain_t gain = tsl.getGain();
}

void simpleRead(void)
{
  uint16_t x = tsl.getLuminosity(TSL2591_VISIBLE);
}

void setup() 
{ 
   Serial.begin(9600);
   dht.begin();
   //soil
   pinMode(SOIL_PIN, INPUT);

  //lux
  configureSensor();
   
   FastLED.setBrightness(80);
   FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
   FastLED.clear();
}

void loop() {
  
  EVERY_N_MILLIS(3600) 
   {
    simpleRead();//lux
    if (tsl.getLuminosity(TSL2591_VISIBLE)< 1100)
    {
      light (true);
      Serial.print("Lux: ");
      Serial.println(tsl.getLuminosity(TSL2591_VISIBLE));
      Serial.println(" -----------------");
    }

    else
    {
      light (false);
      Serial.println("OK");
    }
   }
  
   EVERY_N_MILLIS(3000) 
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
      FastLED.clear();
    }
   }
   
   EVERY_N_MILLIS(3000) 
   {
    int sensorValue = analogRead(SOIL_PIN);
    if (analogRead(SOIL_PIN) >2500)
    {
      light (true);
      Serial.print("Humidity Soil: ");
      Serial.println(analogRead(SOIL_PIN));
      Serial.println(" -----------------");
    }
    else
    {
      FastLED.clear();
    }
   }
  
}
