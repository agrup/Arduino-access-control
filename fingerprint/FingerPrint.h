#ifndef FingerPrint_h 
#define FingerPrint_h 
#include "Arduino.h"

class FingerPrint
{
  public:
    FingerPrint(int pin);
    void enrrol();
    void readfinger();    
  private:
    int _pin;
};

#endif