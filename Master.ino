// Master //
#include <Wire.h>
#include <ArduinoJson.h>

/*const int I2C_SLAVE_ADDR = 0x7F;*/

String response;
char myChar = ' ';
String vacio = String(myChar); 

StaticJsonDocument<16> doc;

void setup()
{
  Serial.begin(115200);
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
  Wire.beginTransmission(0x7F);
  Wire.write(ASK_FOR_LENGTH);
  Wire.endTransmission();

  Wire.requestFrom(0x7F, 1);
  unsigned int responseLength = Wire.read();
  return responseLength;
}

void askForData(unsigned int responseLength)
{
  Wire.beginTransmission(0X7F);
  Wire.write(ASK_FOR_DATA);
  Wire.endTransmission();

  for (int requestIndex = 0; requestIndex <= (responseLength / 32); requestIndex++)
  {
    Wire.requestFrom(0x7F, 16);
    while (Wire.available())
    {
      response += (char)Wire.read();
    }
  }
}

int lux;
int rpm;

void DeserializeResponse()
{
  DeserializationError error = deserializeJson(doc, response);
  if (error) { return; }
 
  lux = doc["lux"];
  rpm = doc["rpm"];
 
  Serial.println(lux);
  Serial.println(rpm);
}