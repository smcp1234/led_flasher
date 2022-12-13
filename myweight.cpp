#include "Arduino.h"
#include "myweight.h"

MyWeight::MyWeight()
{
  
   scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
   long zero_factor = scale.read_average(); //Get a baseline reading
    resetScale();
   Serial.print("Zero Factor = ");
   Serial.println(zero_factor);
  
}

void MyWeight::resetScale(){
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
}
void MyWeight::measureKg(){
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  weight = scale.get_units(5); 
}



