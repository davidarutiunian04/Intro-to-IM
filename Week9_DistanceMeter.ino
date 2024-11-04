long duration;
int distance;

int trigPin = A2;
int echoPin = A1;
int ledPin = 9;
int buttonPin = 7;
int buttonState = LOW;
int previousButtonState = HIGH;  
bool ledState = false;      

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  int currentButtonState = digitalRead(buttonPin);

  if (currentButtonState == LOW && previousButtonState == HIGH) {
    ledState = !ledState;  
    delay(50);           
  }
  previousButtonState = currentButtonState;

  digitalWrite(trigPin, LOW);
  delay(20);
  digitalWrite(trigPin, HIGH);
  delay(20);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  int brightness = 0;

  if (ledState) {  
    if (distance <= 10) {
      brightness = map(distance, 0, 10, 255, 0);
    } else {
      brightness = 0;
    }
  } else {
    brightness = 0; 
  }

  analogWrite(ledPin, brightness);
  delay(10);
}
