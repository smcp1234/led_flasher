#include "Arduino.h"
#include "myfb.h"

MyFB::MyFB()
{
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //Firebase.reconnectWiFi(true);
}

//void MyFB::sendWeight(){
  // set Float  value
 //Firebase.setFloat(data,"weight",weight);
//}

