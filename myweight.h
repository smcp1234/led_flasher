#ifndef myweight_h
#define myweight_h
#include "HX711.h"
class MyWeight
{
public:
    MyWeight();
    void resetScale();
    void measureKg();
    float weight;
    HX711 scale;
    
private:
    float calibration_factor = -341525;
    // HX711 circuit wiring
    const int LOADCELL_DOUT_PIN = 12;
    const int LOADCELL_SCK_PIN = 13;
};

#endif
