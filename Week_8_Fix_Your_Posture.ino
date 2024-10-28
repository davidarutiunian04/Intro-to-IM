void setup() {
pinMode(LED_BUILTIN, OUTPUT); // Red light
pinMode(2,OUTPUT); // Yellow light
pinMode(4,OUTPUT); // Green light

pinMode(A1, INPUT); // Yellow button
pinMode(A2, INPUT); // Green button
}

void loop() {
int yellowState = digitalRead(A1);  // Read the state of yellow button
int greenState = digitalRead(A2);  // Read the state of green button

  if (yellowState == HIGH && greenState == HIGH) {   // When both buttons pressed
    digitalWrite(4, HIGH);    // Turn on green LED
    digitalWrite(2, LOW);    // Turn off yellow LED
    digitalWrite(LED_BUILTIN, LOW);       // Turn off red LED

  } else if (yellowState == HIGH || greenState == HIGH) {  // When only one button pressed
    digitalWrite(4, LOW);     // Turn off green LED
    digitalWrite(2, HIGH);   // Turn on yellow LED
    digitalWrite(LED_BUILTIN, LOW);       // Turn off red LED

  } else {                              // When no button is pressed
    digitalWrite(4, LOW);     // Turn off green LED
    digitalWrite(2, LOW);    // Turn off yellow LED
    digitalWrite(LED_BUILTIN,HIGH);     // Blinking red LED (for 1 second)
    delay(1000);
    digitalWrite(LED_BUILTIN,LOW); 
    delay(1000); 
  }
}