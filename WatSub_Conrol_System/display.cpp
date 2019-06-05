#include "display.h"


bool Display::initialize(){
  bool succesfull = tft.begin(RA8875_800x480);
  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(BRIGHTNESS);

  return succesfull;
}
void Display::set_background(){
    // draw outside circle
  tft.drawCircle(NAV_BALL_CENTER_X_CORD, NAV_BALL_CENTER_Y_CORD, 200, RA8875_WHITE);
  tft.drawCircle(NAV_BALL_CENTER_X_CORD, NAV_BALL_CENTER_Y_CORD, 201, RA8875_WHITE);
  tft.drawCircle(NAV_BALL_CENTER_X_CORD, NAV_BALL_CENTER_Y_CORD, 202, RA8875_WHITE);
}
void Display::Update(){
  if(!dead_mans_switch){
    //tft.fillScreen(RA8875_RED);
    tft.fillCircle(NAV_BALL_CENTER_X_CORD, NAV_BALL_CENTER_Y_CORD, 199, RA8875_RED);
  }
  else{
    //tft.fillScreen(RA8875_BLACK);
    tft.fillCircle(NAV_BALL_CENTER_X_CORD, NAV_BALL_CENTER_Y_CORD, 199, RA8875_BLACK);
  }
  
}
void Display::draw_nav_ball(float pitch, float roll, float heading){
  
  float line_width = sqrt(pow(NAV_BALL_RADIUS, 2) - pow(pitch, 2));
  float x_cord_0 = -line_width, x_cord_1 = line_width;
  float y_cord_0 = -pitch, y_cord_1 = -pitch;
  /*
  Serial.print("X0:");
  Serial.print(x_cord_0);
  Serial.print(" Y0:");
  Serial.print(y_cord_0);
  Serial.print(" X1:");
  Serial.print(x_cord_1);
  Serial.print(" Y1:");
  Serial.print(y_cord_1);
  */
  rotate(x_cord_0, y_cord_0, roll);
  rotate(x_cord_1, y_cord_1, roll);
  /*
  Serial.print(" X0:");
  Serial.print(x_cord_0);
  Serial.print(" Y0:");
  Serial.print(y_cord_0);
  Serial.print(" X1:");
  Serial.print(x_cord_1);
  Serial.print(" Y1:");
  Serial.println(y_cord_1);
  */
  tft.drawLine(round(x_cord_0 + NAV_BALL_CENTER_X_CORD), round(y_cord_0 + NAV_BALL_CENTER_Y_CORD), 
  round(x_cord_1 + NAV_BALL_CENTER_X_CORD), round(y_cord_1 + NAV_BALL_CENTER_Y_CORD), RA8875_BLUE);
}

void Display::write_data(float Vbat){
  tft.setCursor(250, 0);
  tft.setTextColor(RA8875_RED);  tft.setTextSize(2);
  tft.print("Voltage");
}

void rotate(float & x_cord, float & y_cord, float theta){
  float temp_x_cord = x_cord;
  x_cord = (temp_x_cord*cos(theta)) - (y_cord*sin(theta));
  y_cord = (temp_x_cord*sin(theta)) + (y_cord*cos(theta));
}
