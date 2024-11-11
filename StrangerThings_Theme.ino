const int trigPin = 8;
const int echoPin = 12;
const int buttonPin = 7;
const int buzzerPin = 3;

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

long duration;
int distance;
int buttonState = 0;

int SrangerThingsMelody[] = { 
  131, 165, 196, 247, 262, 247, 196, 165, 131, 165, 196, 247, 262, 247, 196, 165, 
  131, 165, 196, 247, 262, 247, 196, 165, 131, 165, 196, 247, 262, 247, 196, 165, 
  131, 165, 196, 247, 262, 247, 196, 165, 131, 165, 196, 247, 262, 247, 196, 165 
};

int StrangerThingsNoteDurations[] = { 
  188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 
  188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 
  188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188 
};

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(buzzerPin, OUTPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) { 
    for (int thisNote = 0; thisNote < 48; thisNote++) {

      // distance measured with ultrasonic sensor

      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2; 

      // mapping the tricolor LED values

      int redValue = map(distance, 5, 50, 255, 100);  
      int greenValue = 0;                             
      int blueValue = map(distance, 5, 50, 100, 255); 

      analogWrite(redPin, redValue);
      analogWrite(greenPin, greenValue);
      analogWrite(bluePin, blueValue);

      // mapping to adjust duration between notes

      int adjustedNoteDuration = map(distance, 5, 50, StrangerThingsNoteDurations[thisNote] / 2, StrangerThingsNoteDurations[thisNote] * 2);

      // playing with the new tempo

      tone(buzzerPin, StrangerThingsMelody[thisNote], adjustedNoteDuration);

      // a short pause

      delay(adjustedNoteDuration * 1.3);
    }

  } else {
    
    // when button is not pressed, turning off the LED and buzzer

    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    noTone(buzzerPin);
  }

  delay(50); 
}