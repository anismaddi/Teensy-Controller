#include <SPI.h>
#include <ADC.h>
#include <IntervalTimer.h>

const byte CS = 10;
const byte LDAC = 12;
const byte analogIn = A5; // Input pin A5
const unsigned int MCP4822_A = 0B0001000000000000;

ADC *adc = new ADC();        // Teensy ADC object
IntervalTimer adcTimer;      // hardware timer

volatile uint16_t adcValue = 0;
volatile bool newSample = false;

void sampleAndSend() {
  // Read fast from ADC0
  uint16_t val = adc->adc0->analogRead(analogIn);
  val &= 0x0FFF;                     
  uint16_t scaledVal = (uint16_t)( ((val-2048)*0.8 +2048 ) ) ; //  gain (x 0.8)

  adcValue = scaledVal;
  newSample = true;

  // Send to DAC (MCP4822)
  digitalWriteFast(CS, LOW);
  SPI.transfer16(MCP4822_A | scaledVal);
  digitalWriteFast(CS, HIGH);
}

void setup() {
  Serial.begin(115200);
  SPI.begin();
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  pinMode(LDAC, OUTPUT);
  digitalWrite(LDAC, LOW);

  // ---- ADC ----
  adc->adc0->setAveraging(0);
  adc->adc0->setResolution(12);
  adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::MED_SPEED); // Speed can be increased
  adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED);

  // ---- SPI ----
  SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));

  // ---- periodic sampling ----
  adcTimer.begin(sampleAndSend, 2.0);  // optional: for stability
}

void loop() {

}
