/*
  Battery.h
*/

#ifndef Battery_h
#define Battery_h

#define FULL_CHARGE 26
#define CLOSE_TO_EMPTY_CHARGE 23.5
#define EMPTY_CHARGE 19.2

class Battery
{
  public:
    Battery();
    void readVoltage(float v);
    int get_life();

  private:
    float pinVoltage = 0;
    float realVoltage = 0;
};

#endif
