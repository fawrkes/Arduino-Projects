/* This code was used on the receving microcontroller of a robotic system
*  This decodes input sent over an XBEE wireless module and translates it
*  to meaningful servo commands.
*
*  Copyright Garrett Parrish 2012
*/

#include <Servo.h>

// Buffer size for NMEA compliant GPS string 
#define DATABUFFERSIZE 80

// initialize data buffer and add 1 for NULL terminator
char dataBuffer[ DATABUFFERSIZE + 1 ];

// startline character
char startChar ='$';

// endline character
char endChar ='\r'; 

// flag to put data in the buffer
boolean storeString = false; 

// empirically tested constants
int servo_roll_center = 77;

// creation of two servo objects
Servo  servo_pitch;
Servo servo_roll;

void setup()
{
    // begin the serial link
    Serial.begin(19200);
}

void servos_attach()
{
    // attach servos to pins on controller
    servo_pitch.attach(11);
    servo_roll.attach(5);
}

void servos_detach()
{
    // detach servos from pins on controller
    servo_pitch.detach();
    servo_roll.detach();
}

boolean getSerialString()
{
    static byte dataBufferIndex = 0;
  
    // if serial data is available
    while( Serial.available() )
    { 
        // reads serial data
        char incomingbyte = Serial.read(); 
    
        // check if first byte is the pre-determined starting character
        if(incomingbyte == startChar)
        {
            // initialize our dataBufferIndex variable
            dataBufferIndex = 0;
            storeString =true; 
          }
          
        // check index here; abort if it's outside buffer size
        // note: uses define here so that databuffersize can be modified
        if(storeString)
        {
            //index is outside of array size: abort
            if(dataBufferIndex == DATABUFFERSIZE){
                dataBufferIndex = 0;
                break;
        }
    
        // check if the incoming byte is the end delimeter
        // the desired string will have been completely transmited
        if(incomingbyte == endChar)
        {
            //null terminate the C string
            //Our data string is complete.
            dataBuffer[dataBufferIndex] = 0;
            return true;
        } 
        else
        {
            //puts data in buffer
            dataBuffer[dataBufferIndex++] = incomingbyte;
            
            //null terminate the C string
            dataBuffer[dataBufferIndex] = 0;
        }
    }
    
    // the arduino has read all the available Serial data and don't have
    // a valid string yet
    return false;
}

// run over and over
void loop() 
{
    //Serial  Decoding
    if(getSerialString())
    {
        // instantiate delimeters
        char delimiters[] ="$,"; 
        char* valPosition;
        
        // splice the string using anArduino method
        valPosition = strtok(dataBuffer, delimiters);
        
        // create an array that the accelerometer data
        // and the button data will be stored in
        int data[] = {0, 0, 0, 0, 0, 0}; 
        
        // store incoming serial data in the array
        for(int i = 0; i < 6; i++)
        { 
            data[i] = atoi(valPosition);
          
            // splice the data via delimeters 
            valPosition = strtok(NULL, delimiters);
        }
      
      // instantiate variables corresponding to the accelerometer and button data
      int accx = data[0];
      int accy = data[1];
      int butz = data[2];
      int butc = data[3];
      int joyx = data[4];
      int joyy = data[5];
    
      /* [EMPIRICALLY DETERMINED CONSTANTS]
      * Servo_pitch_rest = 95
      * accy data ranges from approximately 80 - 180 * accx data ranges feom approximately 80 - 180 * centered accx value is 120 (+/- 5)
      * centered accy value is 130 (+/- 5)
      * centered roll servo value = 87
      * full left position (roll servo) = 10
      * full right postition (roll servo) = 170
      * centered joyx value is 124
      * centered joyy value is 133
      * joyx value ranges from 26 - 214
      * joyy value ranges from 33 - 230 * coordinates of corners:
       - top right - (190, 201)
       - top left - (50, 202)
       - bottom right - (183, 59)
       - bottom left - (51, 58)
      * pressed z and c buttons return 1, unpressed return 0
      * a linear regression of the servo.write() input parameter vs. empirically
      tested angular velocity produced this constant of proportionality: 0.79167 * NOTE: data is received every 50ms
      */
    
      servos_attach();
    
      if (butz == 1)
      {
        servo_pitch.write(100);
    
        // set at center
        servo_roll.write(servo_roll_center); 
      
        if (joyy > 140)
        {
            servo_pitch.write(130);
        }
        else if (joyy < 130)
        {
            servo_pitch.write(97);
        }
      
        if (joyx > 140)
        {
            servo_roll.write(145);
        }
      
        else if (joyx < 110)
        {
            servo_roll.write(45);
        }
    }
  
    else if (butc == 1)
    {
        servo_pitch.write(85);
        servo_roll.write(servo_roll_center);
        
        if (joyy > 140)
        {
            servo_pitch.write(90);
        }
        else if (joyy < 130)
        {
            servo_pitch.write(60);
        }
      
        if (joyx > 140)
        {
            servo_roll.write(45);
        }
        else if (joyx < 110)
        {
            servo_roll.write(145);
        } 
    } 
    
    else 
    { 
        servos_detach(); 
    }
}
