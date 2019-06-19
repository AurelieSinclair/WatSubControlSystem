/*
  Battery.h
*/

#ifndef Battery_h
#define Buoy_h//what?



class Battery
{
  public:
    Battery();
    void get_SOC(int highPin, int groundPin);
    int get_life();
  private:
};

#endif
