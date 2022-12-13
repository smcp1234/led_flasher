#ifndef myfb_h
#define myfb_h
#include <FirebaseESP8266.h>

#define FIREBASE_HOST "iot-weight-project-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "WTbnmepCCVT7sqQlq6FlYBoqCFVnxZ0gEh6knPyE"
class MyFB
{
public:
    MyFB();
    FirebaseData data;
    //void sendWeight();
    //Thread myThread = Thread();
    //void createThread();
    
private:
    
};

#endif
