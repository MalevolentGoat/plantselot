//Plants.a.lot
#include <FastLED.h>//LED Ring
#include <Bounce2.h> //button
#include <DHT.h>;//humidity
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"//lux

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);//lux

// Common naming from FastLED demos
#define DATA_PIN 17
#define NUM_LEDS 12
#define DHTPIN 18 
#define AUDIO_PIN 5;

#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


// How many pulses per minute
uint8_t bpm = 30;

bool Switch = false; //button LED
const int button_pin1 = 12;//buton

//dht22
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

Bounce button1 = Bounce();

// Array of led data
CRGB leds[NUM_LEDS];


void configureSensor(void)
{
  // You can change the gain on the fly, to adapt to brighter/dimmer light situations
  //tsl.setGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
  tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
  //tsl.setGain(TSL2591_GAIN_HIGH);   // 428x gain
  
  // Changing the integration time gives you a longer time over which to sense light
  // longer timelines are slower, but are good in very low light situtations!
  //tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // shortest integration time (bright light)
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS);
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_400MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_500MS);
  // tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);  // longest integration time (dim light)

  /* Display the gain and integration time for reference sake */  
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Gain:         "));
  tsl2591Gain_t gain = tsl.getGain();
  switch(gain)
  {
    case TSL2591_GAIN_LOW:
      Serial.println(F("1x (Low)"));
      break;
    case TSL2591_GAIN_MED:
      Serial.println(F("25x (Medium)"));
      break;
    case TSL2591_GAIN_HIGH:
      Serial.println(F("428x (High)"));
      break;
    case TSL2591_GAIN_MAX:
      Serial.println(F("9876x (Max)"));
      break;
  }
  Serial.print  (F("Timing:       "));
  Serial.print((tsl.getTiming() + 1) * 100, DEC); 
  Serial.println(F(" ms"));
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
}

void setup() 
{ 
   Serial.begin(9600);
   dht.begin();
   
   FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  
   // 8mm Neopixel pins are WS2812B chipset, RGB ordering
   FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
   FastLED.clear();

  button1.attach (12, INPUT_PULLUP);
  pinMode(34, INPUT);

  Serial.println(F("Starting Adafruit TSL2591 Test!"));
  
  if (tsl.begin()) 
  {
    Serial.println(F("Found a TSL2591 sensor"));
  } 
  else 
  {
    Serial.println(F("No sensor found ... check your wiring?"));
    while (1);
  }
  
  /* Configure the sensor */
  configureSensor();//lux
}

void simpleRead(void)
{
  // Simple data read example. Just read the infrared, fullspecrtrum diode 
  // or 'visible' (difference between the two) channels.
  // This can take 100-600 milliseconds! Uncomment whichever of the following you want to read
  uint16_t x = tsl.getLuminosity(TSL2591_VISIBLE);
  //uint16_t x = tsl.getLuminosity(TSL2591_FULLSPECTRUM);
  //uint16_t x = tsl.getLuminosity(TSL2591_INFRARED);

 
  Serial.print(F("Luminosity: "));
  Serial.println(x, DEC);
}

void playAudio() {
    digitalWrite(AUDIO_PIN, HIGH);
    digitalWrite(AUDIO_PIN, LOW);
}

void loop() { 

  button1.update();//led ring
  simpleRead();//lux
  
  if (Switch == false)
  { 
    EVERY_N_MILLIS(2) 
    {
      // Clear strip
        FastLED.clear();
      
        // beat8(x) returns a number from 0 to 255, looping x times per minute
        uint8_t pos = beat8(bpm); 

        // Convert the position to an index for the LED on our strip
        uint8_t led = map8(pos,0,NUM_LEDS-1);
        leds[led] = CRGB::Green;
        FastLED.show();
    }

//   EVERY_N_MILLIS(2) 
//   {
//      // Clear strip
//      FastLED.clear();
//      
//      // beat8(x) returns a number from 0 to 255, looping x times per minute
//      uint8_t pos = beat8(bpm)+127; // so you move it to the other side
//
//      // Convert the position to an index for the LED on our strip
//      uint8_t led = map8(pos,0,NUM_LEDS-1);
//      leds[led] = CRGB::Green;
//      FastLED.show();
//   }
  }

   if(button1.rose())
   {
      Switch = !Switch;
      LEDS.clear(true);
   }

   //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    int sensorValue = analogRead(34);

    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println(" %");
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    Serial.print("Humidity Soil: ");
    Serial.println(sensorValue);
    
}
