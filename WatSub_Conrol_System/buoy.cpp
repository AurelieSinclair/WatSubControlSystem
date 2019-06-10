/*
  Buoy.h
*/

#include "Buoy.h"

Buoy::Buoy(int deadMans, int magnet, int servo)
{
  deadMansPin = deadMans;
  releasePin = magnet;
  servoPin = servo;//might be useless variable

  buoyServo.attach(servoPin);
}

void Buoy::deploy()
{
  
}
