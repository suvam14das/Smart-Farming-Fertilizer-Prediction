#include <SoftwareSerial.h>
#include <Arduino.h>
#include<dht.h>
dht DHT;
#define RX 10
#define TX 11

String AP = "<wifi name>";       // CHANGE ME
String PASS = "<wifi password>"; // CHANGE ME
String API = "<write api key>";   // CHANGE ME
String HOST = "api.thingspeak.com";
String PORT = "80";
String field = "field1";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
SoftwareSerial esp8266(RX,TX); 
 
  
void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
  pinMode(A1,INPUT); 
  pinMode(A3,INPUT);
 
}
void loop() {
 float ldrSensor = analogRead(A0); 
 Serial.println(ldrSensor); 
 int mos = map(analogRead(A1),1023,400,0,100);
 
 DHT.read11(A3);
 float temp = DHT.temperature;
 float humid = DHT.humidity;

 String getData = "GET /update?api_key="+ API +"&field1="+String(ldrSensor)+"&field2="+String(temp)+"&field3="+String(humid)+"&field5="+String(mos);
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }

