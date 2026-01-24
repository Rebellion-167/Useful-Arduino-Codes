#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  // while(!Serial);
  Serial.println("Scanning...");

  for (byte address = 1;address < 127;address++) {
    Wire.beginTransmission(address);
    if(Wire.endTransmission() == 0) {
      Serial.print("I2C device found at 0x");
      Serial.println(address, HEX);
      delay(500);
    }
  }
  Serial.println("Done");
}

void loop() {
  // put your main code here, to run repeatedly:

}
