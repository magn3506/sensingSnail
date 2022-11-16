// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"
#include <SoftwareSerial.h>

#define DHTPIN 13     // Digital pin connected to the DHT sensor

// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

int buzzerPin = 10; 

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(buzzerPin, OUTPUT); // Set buzzer - pin 9 as an output

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  if(h < 75.00) {
     digitalWrite(8, LOW);
     digitalWrite(7, LOW);
     digitalWrite(6, LOW);
     tone(buzzerPin, 1000);
     delay(500);
     noTone(buzzerPin);
  }

  if(h > 75.00 && h < 85.00){
     digitalWrite(8, HIGH);
     digitalWrite(7, LOW);
     digitalWrite(6, LOW);
     tone(buzzerPin, 600);
     delay(500);
     noTone(buzzerPin);
  }

  if(h > 85.00 && h < 95.00){
     digitalWrite(8, LOW);
     digitalWrite(7, HIGH);
     digitalWrite(6, LOW);
     tone(buzzerPin, 400);
     delay(500);
     noTone(buzzerPin);
  }

  if(h > 90.00){
     digitalWrite(8, LOW);
     digitalWrite(7, LOW);
     tone(buzzerPin, 100);
     delay(500);
     noTone(buzzerPin);
  }

}
