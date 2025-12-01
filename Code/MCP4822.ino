#include <SPI.h>
#include <ADC.h>
#include <IntervalTimer.h>

const byte CS = 10;
const byte LDAC = 12;
const byte analogIn = A5;
const unsigned int MCP4822_A = 0B0001000000000000; // Output 1
// const unsigned int MCP4822_A = 0B1001000000000000; // Output 2

ADC *adc = new ADC();        // Teensy ADC object
IntervalTimer adcTimer;      // hardware timer

volatile uint16_t adcValue = 0;
volatile bool newSample = false;

// === Called automatically by the timer ===
void sampleAndSend() {
  // Read fast from ADC0
  uint16_t val = adc->adc0->analogRead(analogIn);
  val &= 0x0FFF;                     // 12-bit mask
  uint16_t scaledVal = (uint16_t)( ((val-2048) +2048 )*0.82 ) ;

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

  // ---- ADC configuration ----
  adc->adc0->setAveraging(0);
  adc->adc0->setResolution(12);
  adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_HIGH_SPEED);
  adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);

  // ---- SPI configuration ----
  SPI.beginTransaction(SPISettings(70000000, MSBFIRST, SPI_MODE0));

  // ---- Start periodic sampling ----
  // 500 kHz sampling = period 2 µs
  adcTimer.begin(sampleAndSend, 2);  // microseconds
}

void loop() {

}
