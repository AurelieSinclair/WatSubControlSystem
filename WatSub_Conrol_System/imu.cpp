#include "Imu.h"

void Imu::initialize() {
  Wire.begin();
  myIMU.begin();
  Wire.setClock(400000); //Increase I2C data rate to 400kHz
  myIMU.enableRotationVector(100); //Send data update every 100ms
}

void Imu::Update(){
  //Look for reports from the IMU
  if (myIMU.dataAvailable() == true)
  {
    float x = myIMU.getQuatI() - offsetX;
    float y = myIMU.getQuatJ() - offsetY;
    float z = myIMU.getQuatK() - offsetZ;
    float w = myIMU.getQuatReal() - offsetW;

    if(i == 2){
      offsetOrientation();
    }
    if(i < 3){
      i++;
    }

    float siny = 2 * (w * z + x * y);
    float cosy = 1 - 2 * (y * y + z * z);
    yaw = atan2(siny, cosy);
    
    float sinp = 2 * (w * y - z * x);
    if(fabs(sinp) >= 1) {
      pitch = copysign(M_PI / 2, sinp);
    }
    pitch = asin(sinp);
    
    float sinr = 2 * (w * x + y * z);
    float cosr = 1 - 2 * (x * x + y * y);
    roll = atan2(sinr, cosr);
  }
}

void Imu::offsetOrientation(){
  offsetX = myIMU.getQuatI();
  offsetY = myIMU.getQuatJ();
  offsetZ = myIMU.getQuatK();
  offsetW = myIMU.getQuatReal();
}

float Imu::get_pitch(){
  return pitch / 100;
}
float Imu::get_yaw(){
  return yaw / 100;
}
float Imu::get_roll(){
  return roll / 100;
}
