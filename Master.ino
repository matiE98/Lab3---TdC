// Master //
#include <Wire.h>
#include <ArduinoJson.h>

const int I2C_SLAVE_ADDR = 0x7F;

String response;
char myChar = ' ';
String vacio = String(myChar); 

StaticJsonDocument<300> doc;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{
  askSlave();
  if (response != vacio) DeserializeResponse();

}

const char ASK_FOR_LENGTH = 'L';
const char ASK_FOR_DATA = 'D';

void askSlave()
{
  response == vacio;

  unsigned int responseLength = askForLength();
  if (responseLength == 0) return;

  askForData(responseLength);
  delay(2000);
}

unsigned int askForLength()
{
  Wire.beginTransmission(I2C_SLAVE_ADDR);
  Wire.write(ASK_FOR_LENGTH);
  Wire.endTransmission();

  Wire.requestFrom(I2C_SLAVE_ADDR, 1);
  unsigned int responseLength = Wire.read();
  return responseLength;
}

void askForData(unsigned int responseLength)
{
  Wire.beginTransmission(I2C_SLAVE_ADDR);
  Wire.write(ASK_FOR_DATA);
  Wire.endTransmission();

  for (int requestIndex = 0; requestIndex <= (responseLength / 32); requestIndex++)
  {
    Wire.requestFrom(I2C_SLAVE_ADDR, responseLength);
    while (Wire.available())
    {
      response += (char)Wire.read();
    }
  }
}

void DeserializeResponse()
{
  DeserializationError error = deserializeJson(doc, response);
  if (error) { return; }
 
  Serial.println(response);
}
