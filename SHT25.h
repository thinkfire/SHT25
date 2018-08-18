/*
  SHT25.h
  Sensirion Humidity sensor SHT25 library for the Arduino microcontroller
  this library used I2C bus.
*/
//#define SHT25_DEBUG

#include <Arduino.h>

#define SHT25_ADDR    0x40 //Sensor addresses

//Commands
#define T_HOLD        0xE3 //trigger T measurement with hold master
#define RH_HOLD       0xE5 //trigger RH measurement with hold master
#define T_NO_HOLD     0xF3 //trigger T measurement with no hold master
#define RH_NO_HOLD    0xF5 //trigger RH measurement with no hold master
#define W_UREG        0xE6 //write user registers
#define R_UREG        0xE7 //read user registers
#define SOFT_RESET         0xFE //soft reset

class SHT25{
  public:
    char begin(void);
    readUserReg(void);
    char writeUserReg(void);
    float getTemperature(void);
    float getHumidity(void);


  private:
    float TEMP, RH;
    float S_T, S_RH;
    char resetSensor(void);

};
