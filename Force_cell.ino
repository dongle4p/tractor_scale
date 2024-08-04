#include <ADS1220_WE.h>
#include <SPI.h>

#define ADS1220_CS_PIN    7 // chip select pin
#define ADS1220_DRDY_PIN  6 // data ready pin 

/* Create your ADS1220 object */
ADS1220_WE ads = ADS1220_WE(ADS1220_CS_PIN, ADS1220_DRDY_PIN);

void setup() {
  Serial.begin(9600);
  if (!ads.init()) {
    Serial.println("ADS1220 is not connected!");
    while (1);
  }

  ads.setCompareChannels(ADS1220_MUX_1_2);
  ads.setGain(ADS1220_GAIN_128);
  ads.setVRefSource(ADS1220_VREF_REFP1_REFN1);
  ads.setVRefValue_V(5.0);  // The exact value doesn't matter!
//  ads.setRefp1Refn1AsVefAndCalibrate(); // That will not work here!!
  ads.setLowSidePowerSwitch(ADS1220_SWITCH);  
} 

void loop() {
  float result = 0.0;
  result = ads.getVoltage_mV(); // get result in millivolts
  Serial.print("Bridge Voltage [mV]: ");
  Serial.println(result, 3);
  
  delay(100);
}