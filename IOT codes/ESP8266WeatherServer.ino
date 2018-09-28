#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// WiFi parameters
const char* ssid = "<wifi name>";
const char* password = "<wifi password>";



const char* getWeatherCondition(){
  // Initialise condition
  const char* condition;
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Declare an object of class HTTPClient
    http.begin("http://api.openweathermap.org/data/2.5/weather?q=Kolkata,IN&appid=017fafd7315089c4937676faa2bf0b99"); // enter city and country code
    int httpCode = http.GET();
 
    if (httpCode > 0) {
      // Get payload
      String payload = http.getString();
      // JSON buffer 
      const size_t bufferSize = JSON_ARRAY_SIZE(3) + 2*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 3*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 480;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      // Parse JSON data
      const char* json = payload.c_str();
      JsonObject& root = jsonBuffer.parseObject(json);
      // Root object
      JsonArray& weather = root["weather"];
      JsonObject& weather0 = weather[0];
      // Get main report
      condition = weather0["main"];
    }
    http.end();   //Close connection
  }
  Serial.println(condition);
  return condition;
}

void setup() {
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Move to next line
  Serial.println();
  // Print WiFi Parameters
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop(){

  getWeatherCondition(); 
   delay(2500);
  
}

