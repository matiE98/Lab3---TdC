bool encontrado = false;

void setup() {
	Serial.begin(9600);
  	Wire.begin();
  	Serial.println("Iniciando deteccion");
}

void loop() {
  for (int i = 0; i<128; i=i+1){
  	Wire.beginTransmission(i);
    byte resultado = Wire.endTransmission();
  	
    if (resultado == 0){
    	Serial.print("Direccion I2C encontrada: ");
      	Serial.println(i, HEX);
      	encontrado = true;
      	delay(100);
    }
  }
  
  if (encontrado = false) {
  		Serial.print("Ningun dispositivo encontrado");
  }
}

