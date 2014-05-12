/* Controller Code for the EMSAR (ElectroMagnetic Swarm Adaptable Robot) *
 * The nunchuk functions (in header file) were adapted off of code produced by TodBot
  *
 * This program reads serial data from a wii nunchuck controller, and transmits
 * it over Xbee wireless modules to the receiver
 *
 * This code was written and compiled in Arduino 1.0 */

//Included Header Files
#include <Wire.h>
#include <Servo.h>
#include "nunchuck_funcs.h"

//Initialization of variables
int  loop_cnt=0;// counter for 100ms loop
byte  accx,accy,butz,butc,joyx,joyy;// bytes that will hold accelerometer and button data

void setup()
{

//the Xbees are set to operate at Baud Rate: 19200 
Serial.begin(19200); 

// Set analog in ports as power and ground for
nunchuck_setpowerpins();

// send the initilization handshake (informs nunchuk that its serial data is being read
nunchuck_init();

Serial.print("WiiChuckDemo ready\n");

}

void loop() {

    // every 100 msecs get new data 
    if( loop_cnt > 50 ) 
    {
        loop_cnt = 0;
        
        // retrieve serial data from nunchuk
        nunchuck_get_data();
        
        // ranges from approx 70 - 182
        accx = nunchuck_accelx(); 
        
        // ranges from approx 65 - 173
        accy = nunchuck_accely(); 
        
        // either 0 or 1
        butz = nunchuck_zbutton();

        // either 0 or 1
        butc = nunchuck_cbutton();
        
        // ranges from FIND joyy = nunchuck_joyy();// ranges from FIND
        joyx = nunchuck_joyx();
        
        // print out data to serial monitor
        Serial.print("$");
        Serial.print((byte)accx,DEC); Serial.print(",");
        Serial.print((byte)accy,DEC); Serial.print(",");
        Serial.print((byte)butz,DEC); Serial.print(",");
        Serial.print((byte)butc,DEC); Serial.print(",");
        Serial.print((byte)joyx,DEC); Serial.print(",");
        Serial.println((byte)joyy,DEC);
        
} loop_cnt++;

// loop again
delay(1); 
}
