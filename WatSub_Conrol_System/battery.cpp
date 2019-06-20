/*
  Battery.h
*/

#include "Battery.h"

Battery::Battery()
{
}

void Battery::readVoltage(float v)
{
  pinVoltage = v * (5 / 1023.0);
  realVoltage = pinVoltage * 11;
}

//Returns the battery charge in percent (0 - 100) ideally
int Battery::get_SOC()
{
  return 100 * (FULL_CHARGE - realVoltage) / (FULL_CHARGE - EMPTY_CHARGE);
}
int Battery::get_life(){
  return 100;//placeholder  
}
