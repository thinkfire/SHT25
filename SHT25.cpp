/*
  Author : Amit Ate
  email  : amitate007@gmail.com
  Description: Sensirion sensor SHT25 is tested with this library on Arduino Uno successefully
*/

#include<SHT25.h>
#include<Wire.h>

SHT25::SHT25(){
  //Do nothing
}

char SHT25::begin(){
  Wire.begin();
  if(resetSensor()){
    return 1;
  }else{return 0;}
}

char SHT25::resetSensor(){
  Wire.beginTransmission(SHT25_ADDR);
  Wire.write(SOFT_RESET);
  char error = Wire.endTransmission();
  if(error == 0){
    delay(15); //wait for sensor to reset
    return 1;
  }else{return 0;}
}
