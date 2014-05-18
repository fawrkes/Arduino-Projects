/*
  Attachment 2 for Lab 7 of ES52
  Garrett / Michael 
 */
 
// Pins
int led = 17;
int pushButton = 4;
int SDO = 10;
int clock = 9;
int count = 0;
int latchEnable = 8;

// Clock/state variables
int clockDelay = 50;
boolean toggle = false;

// Array version of bytes used here (byte version used in attachment three)

// numitron pin number :    5  3  4  8  9  6  7
// numtron pin label:       a  b  c  d  e  f  g
// TLC pin number:         12 11 10  9  8  7  6
int one[]   =             { 0, 1, 1, 0, 0, 0, 0}; // pins 3,4
int two[]   =             { 0, 1, 1, 1, 1, 0, 1}; // pins 3,4,7,8,9
int three[] =             { 1, 1, 1, 1, 0, 0, 1}; // pins 3,4,5,7,8
int four[]  =             { 0, 1, 1, 0, 0, 1, 1}; // pins 3,4,6,7
int five[]  =             { 1, 0, 1, 1, 0, 1, 1}; // pins 4,5,6,7,8
int six[]   =             { 1, 0, 1, 1, 1, 1, 1}; // pins 4,5,6,7,8,9

void setup() {                  
  
  // I/O Pins
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);  
  pinMode(SDO, OUTPUT);
  pinMode(latchEnable, OUTPUT);
  pinMode(clock, OUTPUT);
  
  // Set default values
  digitalWrite(clock, LOW);
  digitalWrite(SDO, LOW);
  digitalWrite(latchEnable, HIGH);  
  
  // Initialize the numitron for testing
  digitalWrite(SDO, HIGH);
  clockPulse();
}

void loop() {
  
    // 'toggle' boolean is used to only trigger a routine when 
    // the button is pressed and not until it is released and then pressed again 
    if (digitalRead(pushButton) == LOW) 
    {
      // Register button press
      if (toggle) 
      {
          toggle = false;
          digitalWrite(SDO, LOW);
          clockPulse();
        }  
    } 
    // Reset boolean when push button is release (allow for another trigger)
    else
    {
      toggle = true;
    }
}

// Helper function to pulse the clock
void clockPulse() {
  digitalWrite(clock, HIGH);
  digitalWrite(clock, LOW);
}

