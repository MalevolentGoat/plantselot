//Plants.a.lot
#include <FastLED.h>//LED Ring
#include <Bounce2.h> //button
#include <DHT.h>;//humidity
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"//lux

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);//lux

// Common naming from FastLED demos
#define DATA_PIN 4
#define NUM_LEDS 12
#define AUDIO_PIN 5
#define SOIL_PIN 34
#define DEBUG_BUTTON 12

//clock
#define RTCAddress 0x68

#define DHTPIN 18 
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

//clock
byte bcd2dec (byte val)
{
  return((val/16*10)+(val%16));
}

byte dec2bcd (byte val)
{
  return((val/10*16)+(val%10));
}

void setTime(byte second, byte minute, byte hour, byte day, byte date, byte month, byte year)
{
  Wire.beginTransmission(RTCAddress);
  Wire.write(0);
  Wire.write(dec2bcd(second));
  Wire.write(dec2bcd(minute));
  Wire.write(dec2bcd(hour));
  Wire.write(dec2bcd(day));
  Wire.write(dec2bcd(date));
  Wire.write(dec2bcd(month));
  Wire.write(dec2bcd(year));
  Wire.endTransmission();
}

void readTime(byte *second, byte *minute, byte *hour, byte *day, byte *date, byte *month, byte *year)
{
  Wire.beginTransmission(RTCAddress);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(RTCAddress, 7);
  *second= bcd2dec(Wire.read() & 0x7F);
  *minute= bcd2dec(Wire.read());
  *hour= bcd2dec(Wire.read()& 0x3F);
  *day= bcd2dec(Wire.read());
  *date= bcd2dec(Wire.read());
  *month= bcd2dec(Wire.read());
  *year= bcd2dec(Wire.read());
  
}

void displayTime()
{
  byte second, minute, hour, day, date, month, year;
  readTime(&second, &minute, &hour, &day, &date, &month, &year);
  Serial.print(second);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(hour);
  Serial.print(":");
  Serial.print("  ");
  Serial.print(day);
  Serial.print(":");
  Serial.print("  ");
  Serial.print(date);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.print(year);
  Serial.println();
}

void light ()
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

   EVERY_N_MILLIS(2) 
   {
      // Clear strip
      FastLED.clear();
      
      // beat8(x) returns a number from 0 to 255, looping x times per minute
      uint8_t pos = beat8(bpm)+127; // so you move it to the other side

      // Convert the position to an index for the LED on our strip
      uint8_t led = map8(pos,0,NUM_LEDS-1);
      leds[led] = CRGB::Green;
      FastLED.show();
   }
}
//lux
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
  tsl2591Gain_t gain = tsl.getGain();
//  switch(gain)
//  {
//    case TSL2591_GAIN_LOW:
//      Serial.println(F("1x (Low)"));
//      break;
//    case TSL2591_GAIN_MED:
//      Serial.println(F("25x (Medium)"));
//      break;
//    case TSL2591_GAIN_HIGH:
//      Serial.println(F("428x (High)"));
//      break;
//    case TSL2591_GAIN_MAX:
//      Serial.println(F("9876x (Max)"));
//      break;
//  }
//  Serial.print  (F("Timing:       "));
//  Serial.print((tsl.getTiming() + 1) * 100, DEC); 
//  Serial.println(F(" ms"));
//  Serial.println(F("------------------------------------"));
//  Serial.println(F(""));
}

void setup() 
{ 
   Serial.begin(9600);
   dht.begin();

   //clock
   Wire.begin(); 
   setTime(0,28,14,4,3,6,21);
   
   FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  
   // 8mm Neopixel pins are WS2812B chipset, RGB ordering
   FastLED.setBrightness(80);
   FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
   FastLED.clear();

  //button
  button1.attach (DEBUG_BUTTON, INPUT_PULLUP);
  pinMode(SOIL_PIN, INPUT);

  
  /* Configure the sensor */
  //lux
  configureSensor();
}

void simpleRead(void)
{
  uint16_t x = tsl.getLuminosity(TSL2591_VISIBLE);
}


void loop() { 

  button1.update();//led ring
//  simpleRead();//lux

  //clock
  displayTime();
  delay(1000);
  
  if (Switch == false)
  { 
    light ();
  }
   if(button1.rose())
   {
      Switch = !Switch;
      LEDS.clear(true);
   }

   //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    int sensorValue = analogRead(SOIL_PIN);

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
