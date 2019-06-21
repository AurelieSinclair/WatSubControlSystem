/*
  Battery.h
*/

#include "Battery.h"

Battery::Battery()
{
}

void Battery::readVoltage(float v)
{
  pinVoltage = v * (3.3 / 4095.0);
  realVoltage = pinVoltage * 11;
}

//Returns the battery charge in percent (0 - 100) ideally
int Battery::get_life()
{
  if (realVoltage < CLOSE_TO_EMPTY_CHARGE){
    return 10 * (realVoltage - EMPTY_CHARGE) / (CLOSE_TO_EMPTY_CHARGE - EMPTY_CHARGE);
  }
  return 10 + 90 * (realVoltage - CLOSE_TO_EMPTY_CHARGE) / (FULL_CHARGE - CLOSE_TO_EMPTY_CHARGE);
}
