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

float SHT25::getHumidity(void){
  if(readByte(RH_NO_HOLD, S_RH, 3, is_RH)){
    RH = -6.0 + 125.0*(S_RH/((long)1<<16));
    return RH;
  }else{return 0;}
}

float SHT25::getTemperature(){
  if(readByte(T_NO_HOLD, S_T, 3, is_TEMP)){
    TEMP = -46.85 + 175.72*(S_T/((long)1<<16));
    return TEMP;
  }else{return 0;}
}

char SHT25::readByte(char CMD, float &value, char length, char para){
  unsigned char data[length];
  Wire.beginTransmission(SHT25_ADDR);
  Wire.write(CMD);
  char error = Wire.endTransmission();
  if(para){
    delay(RH_Delay);
  }else{delay(T_Delay);}

  if(error == 0){
    Wire.requestFrom(SHT25_ADDR, length);
    while (!Wire.available());
    for(char x=0; x<length; x++){
      data[x] = Wire.read();
      x++;
    }
    value = (float)((unsigned int)data[0]*((int)1<<8) + (unsigned int)(data[1]&((int)1<<2)));
    return 1;
  }else{return 0;}
}
