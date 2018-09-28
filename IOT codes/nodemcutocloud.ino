#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <dht.h> 
dht DHT; 

const char* ssid="<wifi name>";
const char* password = "<wifi password>";
char *thingSpeakAddress = "api.thingspeak.com";
unsigned long channelID = <channel id>;
char* readAPIKey = "<read api key>";
char* writeAPIKey = "<write api key>";

unsigned int dataFieldOne = 1;  
WiFiClient client;  

void setup() {
  
  pinMode(D0,OUTPUT);
  digitalWrite(D0,HIGH);

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
int ldr = analogRead(A0); 
Serial.println(ldr);

DHT.read11(D0);
Serial.print(" Humidity " );
int humid = DHT.humidity;
Serial.print(DHT.humidity);
Serial.print(" Temparature ");
int temp = DHT.temperature;
Serial.println(DHT.temperature);

write2TSData(channelID,1,ldr,2,temp,3,humid); 
delay(2000);
}
int write2TSData( long TSChannel, unsigned int TSField1, float field1Data, unsigned int TSField2, long field2Data, unsigned int TSField3, long field3Data ){

  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
  ThingSpeak.setField( TSField3, field3Data );
  
   
  int writeSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  return writeSuccess;
}
