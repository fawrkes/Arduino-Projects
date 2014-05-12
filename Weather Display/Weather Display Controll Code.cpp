// Implementation Arduino Code for ES52 Final Project Design Fair Demo
// Garrett Parrish May 5th, 2014

// for toggling forecast
int Toggle = 9;

// row pins and variables
int R_Out = 10;
int Row1 = 4;
int Row2 = 6;
int Row3 = 11;
int Row4 = 12;
int Row5 = 8;
int Row6 = 13;
int Row7 = 5;
int Row8 = 2;
int Rows[8] = {Row1, Row2, Row3, Row4, Row5, Row6, Row7, Row8};
int currentrow = 0;

// analog sensor pins
int lightIn = 0;
int humidityIn = 1;
int humidityOut = 4;

//false when current data, true when weather API
boolean state = false;

// voltage levels
int PWM_R = 0;
int V_Ld = 0;
int V_H = 0;
word V_light = 0;

void setup()
{
    // set pin modes of all pins
    pinMode(V_light, INPUT);
    pinMode(R_Out, OUTPUT);
    pinMode(Row1, OUTPUT);
    pinMode(Row2, OUTPUT);
    pinMode(Row3, OUTPUT);
    pinMode(Row4, OUTPUT);
    pinMode(Row5, OUTPUT);
    pinMode(Row6, OUTPUT);
    pinMode(Row7, OUTPUT);
    pinMode(Row8, OUTPUT);
    pinMode(Toggle, INPUT);
    
    // set default values
    analogWrite(R_Out, 0);
    digitalWrite(Row1, HIGH);
    digitalWrite(Row2, LOW);
    digitalWrite(Row3, LOW);
    digitalWrite(Row4, LOW);
    digitalWrite(Row5, LOW);
    digitalWrite(Row6, LOW);
    digitalWrite(Row7, LOW);
    digitalWrite(Row8, LOW);
    
    // begin serial monitor
    Serial.begin(4800);
}

// FORECAST DATA -- Taken from ethernet shield program manually
// (since no direct ethernet connection)
int forecastLight = 800;
int forecastHumidity = 4000;

// milliseconds
int standardClock = 550;

// used to toggle between on and off for clock
boolean current_state = HIGH;
int clockRead = 7;

void loop()
{
    
    /* COMMENTED OUT CODE FOR PWM combining from the RED/GREEN LEDs
     if (state == false)
     {
     // read in analog values from Light and Temp Sensor
     // outputs a 10 bits of resolution maping 0V to 0
     // and 5V to 1023
     //    int V_Td = analogRead(V_temp);
     int V_Ld = analogRead(V_light);
     
     //Convert int to volts
     //    int V_T = V_Td*.0049; //Volts per unit
     int V_L = V_Ld*.0049; //Volts per unit
     
     // manipulate inputed voltages to int for Red and Green PWM
     // from 0 to 255 to allow for easy transition to Duty Cycle Value
     PWM_R = 255 * (V_T/5) * (V_L/5);
     //    int PWM_G = 255 * (1 - V_T/5) * (V_L / 5);
     }
     else
     {
     //get PWM_R and PWM_G from weather API
     }
     // write PWM to LEDs
     //  analogWrite(G_Out, PWM_G);
     
     */
    
    
    // FORECAST DATA
    if (digitalRead(Toggle) == HIGH)
    {
        // set V_Ld to brightness of clouds
        V_Ld = forecastLight;
        
        // trigger the clock
        SwitchChange();
        
        // HIGHER HUMIDITY --> LOWER NUMBER (330s) -- standard 400s -- dry (500s)
        
        // delay for the clock
        delay(forecastHumidity);
    }
    // CURRENT DATA
    else
    {
        
        // set humidity out to whatever it's getting in (multiplexed)
        analogWrite(humidityIn, analogRead(humidityIn));
        
        // pulse width modulate the power source
        V_Ld = analogRead(V_light);
        
        // read clock from humidity sensor (rising edge)
        if (digitalRead(clockRead) == HIGH)
        {
            if (current_state != HIGH)
            {
                current_state = HIGH;
                
                Serial.println("CLOCK");
                
                // perform actions on clock edge
                SwitchChange();
            }
        }
        // clock falling edge
        else
        {
            if (current_state != LOW)
            {
                current_state = LOW;
            }  
        }
    }
    
    // pulse width modulate the power source
    analogWrite(R_Out, V_Ld / 4);
}

// iterate to the next row
void SwitchChange()
{
    digitalWrite(Rows[currentrow],LOW);
    currentrow = (currentrow + 1) % 8;
    digitalWrite(Rows[currentrow],HIGH);
} 
