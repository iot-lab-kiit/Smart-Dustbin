int a;  
float distance;
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "ArduinoJson.h"
Servo myservo; 

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;
PubSubClient mqttClient(client);


const char *MQTT_HOST = "14.139.221.186";
const int MQTT_PORT = 61616;
const char *MQTT_CLIENT_ID = "ESP8266 NodeMCU";
const char *MQTT_USER = "artemis";
const char *MQTT_PASSWORD = "artemis";
const char *TOPIC = "IOT.TEST.QUEUE.1";


void setup() {
  // SPI.begin();
  // put your setup code here, to run once:
pinMode(12,OUTPUT);
pinMode(11,INPUT);
pinMode(9,OUTPUT);
pinMode(10,INPUT);
pinMode(6,OUTPUT);
pinMode(7,INPUT);
pinMode(4,OUTPUT); //80% FULLL
pinMode(5,OUTPUT); // Unoccupied


Serial.begin(9600);
myservo.attach(3);
}

void loop() {
  digitalWrite(12,LOW);
  delayMicroseconds(10);
  digitalWrite(12,HIGH);
  delayMicroseconds(10);
  digitalWrite(12,LOW);
  a=pulseIn(11,HIGH);
  distance=a*0.017;

  if (distance<10){
    myservo.write(0);
    delay(5000);
    myservo.write(90);
  }

   digitalWrite(9,LOW);
  delayMicroseconds(10);
  digitalWrite(9,HIGH);
  delayMicroseconds(10);
  digitalWrite(9,LOW);
  int b=pulseIn(10,HIGH);
  delay(25);
  int depth1=b*0.017;


   digitalWrite(6,LOW);
  delayMicroseconds(10);
  digitalWrite(6,HIGH);
  delayMicroseconds(10);
  digitalWrite(6,LOW);
  int c=pulseIn(7,HIGH);
  delay(25);
  int depth2=c*0.017;

  
  int avg= (depth1+depth2)/2;
  String jsonData;

  if(avg<10)
  {
    digitalWrite(5,HIGH);
     jsonData = "{\"dustbinFull\":\"" + String("Yes") + "\",\"latitude\":\"" + String( 20.349856573311364,4) +"\",\"longitude\":\"" + String( 85.8157438539207,4)+"\"}";
  }
  else if (avg>10){
  digitalWrite(5,LOW);
  }
 
    mqttClient.publish(TOPIC,  jsonData.c_str());
    Serial.println(jsonData);
  }