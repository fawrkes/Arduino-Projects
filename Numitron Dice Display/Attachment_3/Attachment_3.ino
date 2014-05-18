/*
  Attachment 3 (byte dataversion) for Lab 7 of ES52
  Garrett / Michael 
 */
 
// Pin Variables
int led = 17;
int pushButton = 4;
int SDO = 10;
int clock = 9;
int count = 0;
int latchEnable = 8;

// State Variables

// Boolean used to only register the pushbutton hit once
boolean toggle = false;

// Corresponding to state of system
int state;

// Clock/count Variables
int clockDelay = 50;

// Delay between iterations on the die
int dieRollDelay;

// Time to wait after button is released
int rollCoolDown;

// Incrementer used (when modded) to iterate through bits
int dieCount = 0;

// Number of numbers on the die
int dieSize = 6;

// Scale used to adjust the cooldown rate of the die
float slowDownScale = 1.2;

// Pin layout for hardware
// numitron pin number :    5  3  4  8  9  6  7
// numtron pin label:       a  b  c  d  e  f  g
// TLC pin number:         12 11 10  9  8  7  6

// Specific bytes corresponding to numbers on numitron
byte one   = B0000110;
byte two   = B1011011;
byte three = B1001111;
byte four  = B1100110;
byte five  = B1101101;
byte six   = B1111101;

// Array of bytes to iterate through
byte nums[] = {one, two, three, four, five, six};

void setup() {                  
  // I/O Pins
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);  
  pinMode(SDO, OUTPUT);
  pinMode(latchEnable, OUTPUT);
  pinMode(clock, OUTPUT);
  state = 0;  
}

void loop() {
  
  // State machine
  switch (state) {
  
    // Initialization
    case 0:     
    
      // Set default values
      digitalWrite(clock, LOW);
      digitalWrite(SDO, LOW);
      digitalWrite(latchEnable, HIGH);  
      
      // Set these here so on a second loop, they
      // can be reset to their initial values
      dieRollDelay = 50;
      rollCoolDown = 2000;
      
      // Move to next state
      state = 1;
      break;
      
    // Wait for button down
    case 1:
    
      // Push button down
      if (digitalRead(pushButton) == LOW) {
        // Move to next state
        state = 2;
      }
      break;
      
    // Start roll
    case 2:
    
      // Generate random start value
      dieCount = random(1,6);
      delay(dieRollDelay);
      
      // Move to next state
      state = 3;
      break;    
      
    // Wait for button relased
    case 3:
    
      // Function that generates increments count
      // and loads that value onto the numitron
      incrementNumitron();

      // Waits for button release 
      if (digitalRead(pushButton) == HIGH) {
        // Move to next state
        state = 4;
      }
      break;
      
    // Wait for roll timeout
    case 4:
    
      // Periodically increase the clock delay
      dieRollDelay *= slowDownScale; 
        
      // Continue to increment numitron
      incrementNumitron();

      // Count down number of milliseconds delayed
      rollCoolDown -= dieRollDelay;

      // When exhausted entire delay --> reset
      if (rollCoolDown < 0) {
        // Reset state to zero
        state = 0;
      }
      break;
  }
}

// Function that increments the numitron display
void incrementNumitron()
{
  dieCount++;
  int number = (dieCount % dieSize);
  numToNumitron(nums[number]);
  delay(dieRollDelay);
}

// Function that takes a byte and outputs a serial signal to 
// the numitron display corresponding to the number it represents
void numToNumitron (byte b) 
{
  // Iterate throgh byte and set output level accordingly
  for (byte mask = 0000001; mask > 0; mask <<= 1) 
  {
    if (b & mask) {
      digitalWrite(SDO, HIGH);
    } else {
      digitalWrite(SDO, LOW); 
    }
    
    // Pulse the clock
    digitalWrite(clock, HIGH);
    digitalWrite(clock, LOW);
  }
}
