/*
  Attachment 1 for Lab 7 of ES52
  Garrett Parrish / Michael 
  */

// Pin Variables
int led = 17;
int pushButton = 4;
int SDO = 10;
int clock = 9;

void setup() {             
  
  // Set pin modes for pins
  pinMode(led, OUTPUT);  
  pinMode(SIO, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(pushButton, INPUT);
}

void loop() {
 
  // Set led high when button pressed
  if (digitalRead(pushButton) == HIGH) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}
