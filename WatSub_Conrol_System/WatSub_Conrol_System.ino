// Zachariah Mears
#include "display.h"
#include "controls.h"

//PA4 is chip select defined in display
//PA3 id reset pin defined in display
//PA5 is sclock
//PA6 is MISO
//PA7 is MOSI
const int voltagePin = PA0;
const int leftPin = PA8;
const int rightPin = PA9;
const int upPin = PB14;
const int downPin = PB15;
const int selectPin = PB7;
const int deadMansPin = PB8;
const int electromagnet = PB5;//check values
const int pitchPin = PB7;
const int yawPin = PB6;

Display display;
Controls controls(leftPin, rightPin, upPin, downPin);
int timeOfUpdate = 0;
int timeOfDeadMansRelease =0;

void setup() {
  
  pinMode(voltagePin, INPUT);
  pinMode(deadMansPin, INPUT);
  display.initialize();
  controls.initialize(pitchPin, yawPin);
  digitalWrite(electromagnet, LOW);
  //Serial.begin(9600);

  display.set_background();
  
  
}

void loop() {
  if(millis() - timeOfUpdate > 300){
  timeOfUpdate = millis();
  display.dead_mans_switch = digitalRead(deadMansPin);
  display.Update();
  display.draw_nav_ball(controls.get_pitch() - 90, controls.get_yaw()- 90, 0);
  display.draw_yaw_rudder(PI*3 /4); //get actuall angle from controls
  //display.write_data(analogRead(voltagePin));
  }
  
    
  controls.update();

  //if dead mans switch released turn screen red and release buoy if longer than 1 s 
  if(digitalRead(deadMansPin) == HIGH){
    if(timeOfDeadMansRelease == 0){
      timeOfDeadMansRelease = millis();
      display.dead_mans_switch = digitalRead(deadMansPin);
      display.Update();
    }
    else if(millis() - timeOfDeadMansRelease > 1000){
      digitalWrite(electromagnet, HIGH);
    }
  }

}
