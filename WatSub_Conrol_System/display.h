#ifndef DISPLAY_H
#define DISPLAY_H
#include "Adafruit_RA8875.h"
#include "Adafruit_GFX.h"

#define CS_PIN PA4 //chip select pin
#define RESET_PIN PA3 //not used but do not connect to anything
#define BRIGHTNESS 255
#define NAV_BALL_CENTER_X_CORD 200
#define NAV_BALL_CENTER_Y_CORD 200
#define NAV_BALL_RADIUS 200



class Display {
  private:
    Adafruit_RA8875 tft = Adafruit_RA8875(CS_PIN, RESET_PIN);
    
  public:
    float roll, pitch, yaw;
    float battery_voltage, current_draw;
    bool dead_mans_switch;
    Display(){
      roll = 0;
      pitch = 0;
      yaw = 0;
      battery_voltage = 0;
      current_draw = 0;
      dead_mans_switch = 0; 
    }
    bool initialize();
    void set_background();
    void Update();
    void write_data(float Vbat);
    void draw_nav_ball(float pitch, float roll, float heading);
    void rotate(float & x_cord, float & y_cord, float theta);
};

void rotate(float & x_cord, float & y_cord, float theta);
#endif
