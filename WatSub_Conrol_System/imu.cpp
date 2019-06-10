#include "Imu.h"

Imu::Imu(HardwareSerial &stream):serial(stream) {
  serial.begin(115200);
  while(!serial);
}

void Imu::update(){
  while (serial.available()) {
    data = serial.read();
    if((counter == 0 && data == 0xAA) || (counter > 0 && counter < 19)){
      rx[counter] = data;
      counter++;
    } else {
      counter = 0;
    }
  }
  if(counter == 19) {
    yaw = (int)rx[4] << 8;
    yaw |= rx[3];
    pitch = (int)rx[6] << 8;
    pitch |= rx[5];
    roll = (int)rx[8] << 8;
    roll |= rx[7];
    
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
