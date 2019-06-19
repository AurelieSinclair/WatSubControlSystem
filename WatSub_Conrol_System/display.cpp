#include "display.h"


bool Display::initialize() {
  bool succesfull = tft.begin(RA8875_800x480);
  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(BRIGHTNESS);

  return succesfull;
}
void Display::set_background() {
  // draw outside circle
  tft.drawCircle(NAV_BALL_CENTER_X_CORD, NAV_BALL_CENTER_Y_CORD, NAV_BALL_RADIUS, RA8875_WHITE);
  tft.drawCircle(NAV_BALL_CENTER_X_CORD, NAV_BALL_CENTER_Y_CORD, NAV_BALL_RADIUS +1, RA8875_WHITE);
  tft.drawCircle(NAV_BALL_CENTER_X_CORD, NAV_BALL_CENTER_Y_CORD, NAV_BALL_RADIUS +2, RA8875_WHITE);
//argument 5 of draw curve is 0, 1,2,3 
  // yaw rudder hull
  tft.drawCurve( YAW_RUDDER_X_CORD -20, 0, 30, YAW_RUDDER_Y_CORD, 0, RA8875_BLUE);
  tft.drawCurve(YAW_RUDDER_X_CORD +20, 0, 30, YAW_RUDDER_Y_CORD,3, RA8875_BLUE);
  tft.drawLine(YAW_RUDDER_X_CORD - 20, YAW_RUDDER_Y_CORD, YAW_RUDDER_X_CORD +20, YAW_RUDDER_Y_CORD, RA8875_BLUE);
  tft.drawLine(YAW_RUDDER_X_CORD , YAW_RUDDER_Y_CORD, YAW_RUDDER_X_CORD , YAW_RUDDER_Y_CORD+ YAW_RUDDER_LEN +50 , RA8875_BLUE);
  //pitch rudder hull
  tft.drawCurve( PITCH_RUDDER_X_CORD, PITCH_RUDDER_Y_CORD - 70,PITCH_RUDDER_LEN +50, 20, 2, RA8875_BLUE);
  tft.drawCurve(PITCH_RUDDER_X_CORD, PITCH_RUDDER_Y_CORD + 70, PITCH_RUDDER_LEN +50, 20,3, RA8875_BLUE);
  tft.drawLine(PITCH_RUDDER_X_CORD + PITCH_RUDDER_LEN +50, PITCH_RUDDER_Y_CORD - 70, 
               PITCH_RUDDER_X_CORD + PITCH_RUDDER_LEN +50, PITCH_RUDDER_Y_CORD + 70, RA8875_BLUE);
  tft.drawLine(PITCH_RUDDER_X_CORD , PITCH_RUDDER_Y_CORD, PITCH_RUDDER_LEN + 50 + PITCH_RUDDER_X_CORD , PITCH_RUDDER_Y_CORD , RA8875_BLUE);
  //battery
  tft.drawRect(BATTERY_TOP_LEFT_X + 20, BATTERY_TOP_LEFT_Y, BATTERY_WIDTH, BATTERY_HEIGTH, RA8875_RED);
  tft.drawRect(BATTERY_TOP_LEFT_X + 21, BATTERY_TOP_LEFT_Y + 1, BATTERY_WIDTH -2, BATTERY_HEIGTH -2, RA8875_RED);
  tft.drawRect(BATTERY_TOP_LEFT_X + 22, BATTERY_TOP_LEFT_Y + 2, BATTERY_WIDTH -4, BATTERY_HEIGTH -4, RA8875_RED);
  tft.drawRect(BATTERY_TOP_LEFT_X + 23, BATTERY_TOP_LEFT_Y + 3, BATTERY_WIDTH -6, BATTERY_HEIGTH -6, RA8875_RED);
  tft.drawRect(BATTERY_TOP_LEFT_X + 24, BATTERY_TOP_LEFT_Y + 4, BATTERY_WIDTH -8, BATTERY_HEIGTH -8, RA8875_RED);
  tft.fillRect(BATTERY_TOP_LEFT_X , BATTERY_TOP_LEFT_Y + 20 , 20, BATTERY_HEIGTH - 40, RA8875_RED);
  
}
void Display::Update() {
  if (!dead_mans_switch) {
    //tft.fillScreen(RA8875_RED);
    tft.fillCircle(NAV_BALL_CENTER_X_CORD, NAV_BALL_CENTER_Y_CORD, NAV_BALL_RADIUS -1, RA8875_RED);
  }
  else {
    //tft.fillScreen(RA8875_BLACK);
    tft.fillCircle(NAV_BALL_CENTER_X_CORD, NAV_BALL_CENTER_Y_CORD, NAV_BALL_RADIUS -1, RA8875_BLACK);
  }
  tft.drawCurve(50, 100, 80, 40, 2, RA8875_GREEN);

}
void Display::draw_nav_ball(float pitch, float roll, float heading) {

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

void Display::draw_yaw_rudder(float yaw_angle){
  tft.drawLine(YAW_RUDDER_X_CORD , YAW_RUDDER_Y_CORD, YAW_RUDDER_X_CORD , YAW_RUDDER_Y_CORD+ YAW_RUDDER_LEN +50 , RA8875_BLUE);
  tft.drawLine(YAW_RUDDER_X_CORD, YAW_RUDDER_Y_CORD, round( YAW_RUDDER_X_CORD +( YAW_RUDDER_LEN * cos(yaw_angle))),
               round( YAW_RUDDER_Y_CORD + YAW_RUDDER_LEN * sin(yaw_angle)),RA8875_GREEN);
  tft.drawLine(YAW_RUDDER_X_CORD + 1, YAW_RUDDER_Y_CORD, round( YAW_RUDDER_X_CORD +( YAW_RUDDER_LEN * cos(yaw_angle))) +1,
               round( YAW_RUDDER_Y_CORD + YAW_RUDDER_LEN * sin(yaw_angle)),RA8875_GREEN);
  tft.drawLine(YAW_RUDDER_X_CORD -1, YAW_RUDDER_Y_CORD, round( YAW_RUDDER_X_CORD +( YAW_RUDDER_LEN * cos(yaw_angle))) -1,
               round( YAW_RUDDER_Y_CORD + YAW_RUDDER_LEN * sin(yaw_angle)),RA8875_GREEN);
  tft.drawLine(YAW_RUDDER_X_CORD + 2, YAW_RUDDER_Y_CORD, round( YAW_RUDDER_X_CORD +( YAW_RUDDER_LEN * cos(yaw_angle))) +2,
               round( YAW_RUDDER_Y_CORD + YAW_RUDDER_LEN * sin(yaw_angle)),RA8875_GREEN);
  tft.drawLine(YAW_RUDDER_X_CORD -2, YAW_RUDDER_Y_CORD, round( YAW_RUDDER_X_CORD +( YAW_RUDDER_LEN * cos(yaw_angle))) -2,
               round( YAW_RUDDER_Y_CORD + YAW_RUDDER_LEN * sin(yaw_angle)),RA8875_GREEN);
}
//btween 7 degrees up and down max approx
void Display::draw_pitch_rudder(float pitch_angle){
  //make pretty
  tft.drawLine(PITCH_RUDDER_X_CORD , PITCH_RUDDER_Y_CORD, PITCH_RUDDER_LEN + 50 + PITCH_RUDDER_X_CORD , PITCH_RUDDER_Y_CORD , RA8875_BLUE);
  tft.drawLine(PITCH_RUDDER_X_CORD, PITCH_RUDDER_Y_CORD, round( PITCH_RUDDER_X_CORD +( PITCH_RUDDER_LEN * sin(pitch_angle))),
               round( PITCH_RUDDER_Y_CORD + PITCH_RUDDER_LEN * cos(pitch_angle)),RA8875_GREEN);
  tft.drawLine(PITCH_RUDDER_X_CORD, PITCH_RUDDER_Y_CORD - 1, round( PITCH_RUDDER_X_CORD +(PITCH_RUDDER_LEN * sin(pitch_angle))),
               round( PITCH_RUDDER_Y_CORD + PITCH_RUDDER_LEN * cos(pitch_angle)) - 1,RA8875_GREEN);
  tft.drawLine(PITCH_RUDDER_X_CORD, PITCH_RUDDER_Y_CORD + 1, round( PITCH_RUDDER_X_CORD +(PITCH_RUDDER_LEN * sin(pitch_angle))),
               round( PITCH_RUDDER_Y_CORD + PITCH_RUDDER_LEN * cos(pitch_angle)) + 1,RA8875_GREEN);
               
  tft.drawLine(PITCH_RUDDER_X_CORD, PITCH_RUDDER_Y_CORD + 2, round( PITCH_RUDDER_X_CORD +(PITCH_RUDDER_LEN * sin(pitch_angle))),
               round( PITCH_RUDDER_Y_CORD + PITCH_RUDDER_LEN * cos(pitch_angle)) + 2,RA8875_GREEN);
  tft.drawLine(PITCH_RUDDER_X_CORD, PITCH_RUDDER_Y_CORD + 2, round( PITCH_RUDDER_X_CORD +(PITCH_RUDDER_LEN * sin(pitch_angle))),
               round( PITCH_RUDDER_Y_CORD + PITCH_RUDDER_LEN * cos(pitch_angle)) + 2,RA8875_GREEN);
}

void Display::battery_life(int battery_left){
  if(battery_left != battery_displayed){
    tft.fillRect(BATTERY_TOP_LEFT_X + round(BATTERY_WIDTH *(1 - battery_left/100.0)) + 28, BATTERY_TOP_LEFT_Y +8,
                 round(BATTERY_WIDTH * battery_left/106)  , BATTERY_HEIGTH -16, RA8875_RED);
  }
}
  
void Display::write_data(float Vbat) {
  tft.setCursor(250, 0);
  tft.setTextColor(RA8875_RED);  tft.setTextSize(2);
  tft.print("Voltage");
}

void Display::rotate(float & x_cord, float & y_cord, float theta) {
  float temp_x_cord = x_cord;
  x_cord = (temp_x_cord * cos(theta)) - (y_cord * sin(theta));
  y_cord = (temp_x_cord * sin(theta)) + (y_cord * cos(theta));
}
