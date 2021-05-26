//Plants.a.lot
#include <FastLED.h>
#include <Bounce2.h> 
#include <DHT.h>;


// Common naming from FastLED demos
#define DATA_PIN 17
#define NUM_LEDS 12
#define DHTPIN 23 

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
}


void loop() { 

  button1.update();
  
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
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    Serial.print("Humidity Soil: ");
    Serial.println(sensorValue);
    
}
