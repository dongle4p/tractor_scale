#include <ADS1220_WE.h>
#include <SPI.h>
#include <math.h>

#define ADS1220_CS_PIN    7 
#define ADS1220_DRDY_PIN  6 

ADS1220_WE ads = ADS1220_WE(ADS1220_CS_PIN, ADS1220_DRDY_PIN);

unsigned long previousMillis = 0;  
const long interval = 0.67;  // Interval in milliseconds

void setup() {
  Serial.begin(115200);
  if (!ads.init()) {
    Serial.println("ADS1220 is not connected!");
    while (1);
  }

  ads.setCompareChannels(ADS1220_MUX_1_2);
  ads.setGain(ADS1220_GAIN_128);
  ads.setVRefSource(ADS1220_VREF_REFP1_REFN1);
  ads.setVRefValue_V(5.0);  
  ads.setLowSidePowerSwitch(ADS1220_SWITCH);
  ads.setDataRate(1500);

}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float result = ads.getVoltage_mV();
   // float weight = abs(result);
    Serial.println(result,3);

  }
}
