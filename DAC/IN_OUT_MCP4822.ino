#include <SPI.h>

const byte CS = 10;
const byte LDAC = 12;
const byte analogIn = A5; // Read the analog input A5
const unsigned int MCP4822_A = 0B0011000000000000;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  pinMode(LDAC, OUTPUT);
  digitalWrite(LDAC, LOW);

  analogReadResolution(10); 
}

void loop() {
  unsigned int adcValue = analogRead(analogIn);
  if (adcValue > 4095) adcValue = 4095;  // sécurité

  // SPI
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CS, LOW);
  SPI.transfer16(MCP4822_A | adcValue);
  digitalWrite(CS, HIGH);
  SPI.endTransaction();

  Serial.println(adcValue);
}
