#include "controls.h"

Controls::Controls(int left_pin, int right_pin, int up_pin, int down_pin) {
  pitch = 0, currently_pitching = 0, pitch_start_time = 0;
  yaw = 0, currently_yawing = 0, yaw_start_time = 0;
  left_button = left_pin;
  right_button = right_pin;
  up_button = up_pin;
  down_button = down_pin;
}
    
void Controls::initialize(int pitch_pin, int yaw_pin){
  pitchServo.attach(pitch_pin);
  yawServo.attach(yaw_pin);
  pinMode(left_button, INPUT_PULLDOWN);
  pinMode(right_button, INPUT_PULLDOWN);
  pinMode(up_button, INPUT_PULLDOWN);
  pinMode(down_button, INPUT_PULLDOWN);
}

void Controls::update(){
  if(digitalRead(left_button) == HIGH){
    if(currently_yawing == 1){
      yaw = YAW_CENTER_POS + INVERT_YAW * (INSTANT_YAW_AMOUNT + (millis() - yaw_start_time) * YAW_RATE);
    }
    else{
      currently_yawing = 1;
      yaw_start_time = millis();
    }
  }
  else if(digitalRead(right_button) == HIGH){
    if(currently_yawing == 2){
      yaw = YAW_CENTER_POS - INVERT_YAW * (INSTANT_YAW_AMOUNT + (millis() - yaw_start_time) * YAW_RATE);
    }
    else{
      currently_yawing = 2;
      yaw_start_time = millis();
    }
  }
  else{
    yaw = YAW_CENTER_POS;
    currently_yawing = 0;
  }
  if(digitalRead(up_button) == HIGH){
    if(currently_pitching == 1){
      pitch = PITCH_CENTER_POS + INVERT_PITCH * (INSTANT_PITCH_AMOUNT + (millis() - pitch_start_time) * PITCH_RATE);
    }
    else{
      currently_pitching = 1;
      pitch_start_time = millis();
    }
  }
  else if(digitalRead(down_button) == HIGH){
    if(currently_pitching == 2){
      pitch = PITCH_CENTER_POS - INVERT_PITCH * (INSTANT_PITCH_AMOUNT + (millis() - pitch_start_time) * PITCH_RATE);
    }
    else{
      currently_pitching = 2;
      pitch_start_time = millis();
    }
  }
  else{
    pitch = PITCH_CENTER_POS;
    currently_pitching = 0;
  }
  pitch = constrain(pitch, 0, 180);
  yaw = constrain(yaw, 0, 180);
  pitchServo.write(pitch);
  yawServo.write(yaw);
}

int Controls::get_pitch(){
  return pitch;
}
int Controls::get_yaw(){
  return yaw;
}
