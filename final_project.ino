#include <DHT.h>

const int ledPin = 13;         
const int ldrPin = A0;        
const int dhtPin = 7;          
const int pulsePin = A1;       

int Signal;                    
int ldrValue;
int Threshold = 550;           
unsigned long lastBeatTime = 0; 
unsigned long currentMillis;  
unsigned long timeBetweenBeats = 0; 
int BPM = 0;                 
bool pulseDetected = false;    

#define DHTTYPE DHT22         

DHT dht(dhtPin, DHT22);     

const int lightThreshold = 100;

//threshold for signals from the pulse sensor
const int minRawSignal = 60;
const int maxRawSignal = 150;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);  
  
  Serial.begin(9600);

  dht.begin();
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); 

  Signal = analogRead(pulsePin); 

  Serial.print(ldrValue);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(Signal);

  if (Signal < minRawSignal) {
    Signal = minRawSignal; 
  } else if (Signal > maxRawSignal) {
    Signal = maxRawSignal;
  }

  // detecting heartbeat 
  if (Signal > Threshold && !pulseDetected) {
    currentMillis = millis();  
    timeBetweenBeats = currentMillis - lastBeatTime;
    pulseDetected = true; 
  }

  if (Signal < Threshold) {
    pulseDetected = false;
  }

// controling the LED according to the LDR value
  if (ldrValue > lightThreshold) {
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, HIGH);
  }

  delay(10);
}
