#include <Arduino.h>
#include <SHT25.h>

SHT25 RH_SENS;

void setup() {
    Serial.begin(9600);
    if(RH_SENS.begin()){
      Serial.println("Begin Successful!");
    }else{Serial.println("Begin Failed!");}
}

void loop() {

  Serial.println(RH_SENS.getHumidity(),2);

  delay(5000);

}
