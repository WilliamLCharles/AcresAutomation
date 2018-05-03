/*
Developer: William Charles
Time Stamp: August, 2018
Help from: Ladyada, Sparkfun, Adafruit, Particle
*/

#include <Adafruit_DHT.h>
// DHT humidity/temperature and VH400 soil humidity sensor array

#define DHTPIN 5     // what pin we're connected to, D5

#define DHTTYPE DHT22		// DHT 22 (AM2302)

int soilHum;
int mval = 0;
int val = 0;
// Pins
int VH400 = A4;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600); 
	Serial.println("DHT22 INIT");

pinMode(VH400, INPUT);

	dht.begin();
}

void loop() {
// Wait a few seconds between measurements.
	delay(2000);

// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a 
// very slow sensor)
	float h = dht.getHumidity();
// Read temperature as Celsius
	float t = dht.getTempCelcius();
// Read temperature as Farenheit
	float f = dht.getTempFarenheit();
  
// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) || isnan(f)) {
		Serial.println("DHT22 INIT FAILED");
		return;
	}

//Publishing these variables---- *this will change with Xenon*
  Particle.variable("Temperature", String(t) + " °C");
  delay(1000);
  	
  Particle.variable("Temperature", String(f) + " °F");
  delay(1000);
  
  Particle.variable("Humidity", String(h) + " %");
  delay(1000);

//VH400 Readings
  
    val = analogRead(VH400);

    mval = map(val, 3, 3650, 0, 100);
Particle.variable("SoilMoist:", mval);
delay(500);


}

