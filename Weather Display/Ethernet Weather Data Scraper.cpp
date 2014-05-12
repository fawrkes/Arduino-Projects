// Arduino Ethernet/JSON forecast data code
// Garrett Parrish - ES52 April 29th
  
#include <Ethernet.h>
#include <aJSON.h>
#include <String.h>
#include <SPI.h>
 
// mac address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// local IP address
IPAddress ip (192,168,1,150);
 
// first API call to get city location
char ipAPI[] = "api.hostip.info";

// second API call to get actual weather data
char weatherAPI[] = "api.openweathermap.org";
 
// ehternet client
EthernetClient client;
 
// http response variables
String http_response  = "";
int    response_start = 0;
int    response_end   = 0;
 
// string responses from internet requests
String country_name = "";
String country_code = "";
String city_name = "";
String ip_from_request = "";
 
void setup() 
{
  // initialize serial monitor
  Serial.begin(9600);
  
  // begin ethernet connection
  Ethernet.begin(mac, ip);

  // print out for debugging 
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  Serial.println();
  Serial.println("Connecting...");
  Serial.println();
}
 
void loop() 
{
  // request ip info from first host, fetch json, and get strings from result
  aJsonObject* IP = requestHTTPResponse(ipAPI, "/get_json.php");      
  
  // save variables from JSON object
  aJsonObject* countryNameJSON = aJson.getObjectItem(IP, "country_name");
  aJsonObject* countryCodeJSON = aJson.getObjectItem(IP, "country_code");
  aJsonObject* cityJSON = aJson.getObjectItem(IP, "city");
  aJsonObject* ipJSON = aJson.getObjectItem(IP, "ip");
 
  delay(500);

  // pull out strings from the json data
  country_name = countryNameJSON->valuestring;    
  country_code = countryCodeJSON->valuestring;
  city_name = cityJSON->valuestring;
  ip_from_request = ipJSON->valuestring;
  
  delay(500);   

  // if there was a response and city_name was found (input to weather API query) 
  if (city_name != "")
  {
    // request the actual weather data (pass it the query string + city name)
    aJsonObject* weatherDataJSON = requestHTTPResponse(weatherAPI, "/data/2.5/weather?q=" + city_name);
    aJsonObject* mainJSON = aJson.getObjectItem(weatherDataJSON,"main");

    // humidity (int from 1 - 100)
    aJsonObject* humidityJSON = aJson.getObjectItem(mainJSON, "humidity");
    String humidityStr = humidityJSON->valuestring;
    int humidity = humidityStr.toInt();
    Serial.println(humidity);

    // percentage humidity (same input as voltage from analog circuit)
    float humidityPercentage = (float)humidity/100.0;
    
    // temperature (float in kelvin)
    aJsonObject* temperatureJSON = aJson.getObjectItem(mainJSON, "temp");
    String temperatureStr = temperatureJSON->valuestring;
    int temperature = temperatureStr.toInt();
    Serial.println(temperature);
    
    // NOTE: I can't do the actual converting of the temperature to a meaningful digital
    // value because we do not have the temperature sensor to empirically test with

    // percentage of cloud cover (int from 0 - 100)             
    aJsonObject* cloudsJSON = aJson.getObjectItem(weatherDataJSON, "clouds");
    aJsonObject* brightnessJSON = aJson.getObjectItem(cloudsJSON, "all"); 
    String brightnessStr = brightnessJSON->valuestring;
    int brightness = brightnessStr.toInt();
    Serial.println(brightness);

    // percentage brighntess (same input as voltage from analog circuit)
    float brightnessPercentage = (float)brightness/100.0;
  }
  
  // retry every second
  delay(1000);
}

aJsonObject* requestHTTPResponse(char host[], String query)
{
  http_response = "";
  response_start = 0;
  response_end = 0;
  char c[] = "";
  char buffer[10];

  // connect to IP host (port 80)
  client.connect(host, 80);

  // query the php script (in this case with nothing)  
  client.println("GET "+ query +" HTTP/1.1");

  client.println("Host: " + str(host));
  client.println("User-Agent: Mozilla/5.0");
  client.println("Connection: close");
  client.println();
  delay(500);
  
  // get starting and ending indexes of the response data
  response_start = http_response.indexOf("<data>")+6; 
  response_end = http_response.indexOf("</data>"); 

  // pull out the string
  http_response = http_response.substring(response_start,response_end); 
 
  Serial.print("HTTP response : ");
  Serial.println(http_response);
  Serial.println(); 
 
  // stop the connection to the server
  client.stop();
 
  // make a new string for the JSON from the HTTP request
  char httpJSON[http_response.length()+1];
 
  http_response.toCharArray(httpJSON, http_response.length()+1);

  // create a new json object from parsing the JSON string
  aJsonObject* jsonObject = aJson.parse(httpJSON);
  delay(200);

  return jsonObject;  
}