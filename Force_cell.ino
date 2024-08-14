#include <ADS1220_WE.h>
#include <SPI.h>

#define ADS1220_CS_PIN    7 
#define ADS1220_DRDY_PIN  6 

ADS1220_WE ads = ADS1220_WE(ADS1220_CS_PIN, ADS1220_DRDY_PIN);

unsigned long previousMillis = 0;  
const long interval = 0.6;  // Interval in milliseconds
const int numMeasurements = 100; // Number of measurements to average
float off = 0.0;

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
  ads.setFIRFilter(ADS1220_50HZ_60HZ);
  // Initialize offset calculation
  float sum = 0.0;
  for (int i = 0; i < numMeasurements; i++) {
    float voltage = ads.getVoltage_mV();
    sum += 116.279 * voltage;
  }

  off = sum / numMeasurements;

  // Print the calculated offset for debugging
  Serial.print("Calculated offset: ");
  Serial.println(off, 3);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Apply the adjustment to the current reading
    float result = 116.279* ads.getVoltage_mV() -off;
    Serial.println(result, 3);
   // Serial.println(off);
  }
}
