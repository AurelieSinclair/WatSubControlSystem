#include "Imu.h"

void Imu::initialize() {
  Serial1.begin(115200);
  while(!Serial1);
}

void Imu::Update(){
  while (Serial1.available()) {
    data = Serial1.read();
    if(((counter == 0 || counter == 1) && data == 0xAA) || (counter > 1 && counter < 19)){
      rx[counter] = data;
      counter++;
    } else {
      if(counter >= 19){
        yaw = (int)rx[4] << 8;
        yaw |= rx[3];
        pitch = (int)rx[6] << 8;
        pitch |= rx[5];
        roll = (int)rx[8] << 8;
        roll |= rx[7];
      }
      counter = 0;
  }
}

int Imu::get_pitch(){
  return pitch;
}
int Imu::get_yaw(){
  return yaw;
}
int Imu::get_roll(){
  return roll;
}
