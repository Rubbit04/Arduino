#define pinLED 8

void setup() {

 pinMode(pinLED, OUTPUT);  
}

void loop() {
  
  digitalWrite(pinLED, HIGH); // enciende el LED.
  delay(500); // retardo en milisegundos
  digitalWrite(pinLED, LOW); // apaga el LED.
  delay(500); 
}
