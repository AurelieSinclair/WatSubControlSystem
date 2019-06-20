/*
  Battery.h
*/

#ifndef Battery_h
#define Buoy_h//what?

#define FULL_CHARGE 29.5
#define EMPTY_CHARGE 19.0

class Battery
{
  public:
    Battery();
<<<<<<< Updated upstream
    void get_SOC(int highPin, int groundPin);
    int get_life();
=======
    void readVoltage(float v);
    int get_SOC();

>>>>>>> Stashed changes
  private:
    float pinVoltage = 0;
    float realVoltage = 0;
};

#endif
