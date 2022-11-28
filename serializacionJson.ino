#include <Wire.h>
#include <ArduinoJson.h>

int luz = 0;
int velocidad = 0;
bool var = true;
float voltage;
float luxes;
float resistance;

const float LUX_CALC_SCALAR=12518931;
const float LUX_CALC_EXPONENT=-1.405;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (var == true) {
    
    luz = random(0,1023);
	  velocidad = map(luz, 0, 1023, 1, 3);
    voltage = luz * (5.0/1023) * 1000;
    resistance = 10000 * ( voltage / ( 5000.0 - voltage) );
    luxes = LUX_CALC_SCALAR * pow(resistance, LUX_CALC_EXPONENT);
     
    char json[300];
    StaticJsonDocument<192> doc; 
    
    doc["controller_name"] = "Arduino-nano-5";
    doc["date"] = "2022-27-11 20:28:00";
    
    // Armando el array actuators
    JsonArray arrActuator = doc.createNestedArray("actuators");
    StaticJsonDocument<52> act;
    JsonObject actuator = act.to<JsonObject>();
    actuator["type"]="stepper";
    actuator["current_value"] = velocidad;
    arrActuator.add(actuator);
    
    // Armando el array sensors
    JsonArray arrSensor = doc.createNestedArray("sensors");
    StaticJsonDocument<52> sen;
    JsonObject sensor = sen.to<JsonObject>();
    sensor["type"]="fotorresistor";
    sensor["current_value"] = luxes;
    arrSensor.add(sensor);  
    
    serializeJsonPretty(doc, json);
    Serial.print("Json: ");
    Serial.println(json);
  }
  delay(2000);
}

