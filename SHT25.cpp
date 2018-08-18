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
    RH_Delay = selectDelay(RH_NO_HOLD, RES_RH);
    T_Delay  = selectDelay(T_NO_HOLD, RES_T);
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

float SHT25::getHumidity(){
  if(readByte(RH_NO_HOLD, S_RH, 3)){
    return 1.0;
  }else{return 0.1;}
}

float SHT25::getTemperature(){


}

char SHT25::readByte(char CMD, unsigned int &value, char length){

  unsigned char data[length];
  Wire.beginTransmission(SHT25_ADDR);
  Wire.write(CMD);
  char error = Wire.endTransmission();
  if(CMD == RH_NO_HOLD){
    delay(RH_Delay);
  }else{delay(T_Delay);}
  Serial.println(RH_Delay);
  if(error == 0){
    Wire.requestFrom(SHT25_ADDR, length);
    while (!Wire.available());
    Serial.println("in readByte");
    for(char x=0; x<length; x++){
      data[x] = Wire.read();
      x++;
    }
    Serial.print("data[0] - ");
    Serial.println(data[0]);
    Serial.print("data[1] - ");
    Serial.println(data[1]);
    Serial.print("data[2] - ");
    Serial.println(data[2]);


    unsigned int value1 = (unsigned int)data[0]*((int)1<<8) + (unsigned int)(data[1]&((int)1<<2));

    Serial.print("Value - ");
    Serial.println(value1);

    return 1;
  }else{return 0;}
}

int SHT25::selectDelay(char CMD, char RES){
  switch (CMD) {
    case T_NO_HOLD:
      switch (RES) {
        case 11:
          T_Delay = 11;
          break;
        case 12:
          T_Delay = 22;
          break;
        case 13:
          T_Delay = 43;
          break;
        case 14:
          T_Delay = 85;
          break;
        default:
          T_Delay = 85;
          break;
      };
      break;
    case RH_NO_HOLD:
      switch (RES) {
        case 8:
          RH_Delay = 4;
          break;
        case 10:
          RH_Delay = 9;
          break;
        case 11:
          RH_Delay = 15;
          break;
        case 12:
          RH_Delay = 29;
          break;
        default:
          RH_Delay = 29;
          break;
      };
      break;
  }
}
