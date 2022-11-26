#include <Wire.h>
#include <ArduinoJson.h>

int luz = 0;
int rpm = 0;

char json[21];
StaticJsonDocument<16> doc;    

void SerializeObject()
{    
  luz = random(0, 1023);
  rpm = map(luz, 0, 1023, 0, 3);  
    
  doc["lux"]=luz;
  doc["rpm"]=rpm;
  	
  serializeJson(doc, json);
  Serial.print("Json: ");
  Serial.println(json); 
}

void setup()
{
  Serial.begin(9600);

  SerializeObject();

  Wire.begin(0x7F);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

const char ASK_FOR_LENGTH = 'L';
const char ASK_FOR_DATA = 'D';


char request = ' ';
char requestIndex = 0;

void receiveEvent(int bytes)
{
  while (Wire.available())
  {
   request = (char)Wire.read();
  }
}

void requestEvent()
{
  if(request == ASK_FOR_LENGTH)
  {
    Wire.write(21);
    char requestIndex = 0;
  }
   
  if(request == ASK_FOR_DATA)
  {
    if(requestIndex < (21 / 32)) 
    {
       Wire.write(json, 16);
       requestIndex ++;
    }
    else
    {
      Wire.write(json, 16);
      requestIndex = 0;
    }
  }
}

void loop() 
{
}