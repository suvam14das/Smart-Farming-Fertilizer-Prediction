#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid="<wifi name>";
const char* password = "<wifi password>";
char *thingSpeakAddress = "api.thingspeak.com";
unsigned long channelID =  <channel id >;
char* readAPIKey = "<read api key>";

unsigned int dataFieldOne = 1;
unsigned int dataFieldTwo = 2;  
unsigned int dataFieldThree = 3;    
WiFiClient client;  

void setup() {
  
  pinMode(D0,OUTPUT);
  digitalWrite(D0,HIGH);
  pinMode(D1,OUTPUT);
  digitalWrite(D1,HIGH);
  pinMode(D2,OUTPUT);
  digitalWrite(D2,HIGH);

  Serial.begin(115200);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }

  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );
  ThingSpeak.begin( client );

}

void loop() {
  // put your main code here, to run repeatedly:
int lighting = readTSData( channelID, dataFieldOne);
int ventilation = readTSData( channelID, dataFieldTwo);
int watering = readTSData( channelID, dataFieldThree);
if(lighting==1) digitalWrite(D0,0); 
else digitalWrite(D0,1); 
if(ventilation==1) digitalWrite(D1,0); 
else digitalWrite(D1,1); 
if(watering==1) digitalWrite(D2,0); 
else digitalWrite(D2,1); 

Serial.println(lighting," ",ventilation," ",watering); 
}
int readTSData( long TSChannel,unsigned int TSField ){
    
  int data =  ThingSpeak.readIntField( TSChannel, TSField, readAPIKey );
  Serial.println( " Data read from ThingSpeak: " + String( data, 9 ) );
  return data; 
  
}

