#include <ADS1220_WE.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#define ADS1220_CS_PIN    7 // chip select pin
#define ADS1220_DRDY_PIN  6 // data ready pin 
#define BT_RX_PIN         10 // Bluetooth HC-05 RX pin
#define BT_TX_PIN         11 // Bluetooth HC-05 TX pin

/* Create your ADS1220 object */
ADS1220_WE ads = ADS1220_WE(ADS1220_CS_PIN, ADS1220_DRDY_PIN);
/* Create a SoftwareSerial object for Bluetooth communication */
SoftwareSerial btSerial(BT_RX_PIN, BT_TX_PIN);

void setup() {
  btSerial.begin(9600); // For Bluetooth communication
  
  if (!ads.init()) {
    btSerial.println("ADS1220 is not connected!"); // Send error message via Bluetooth
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
  
  // Send result via Bluetooth
  btSerial.print("Bridge Voltage [mV]: ");
  btSerial.println(result, 3);
  
  delay(100);
}
