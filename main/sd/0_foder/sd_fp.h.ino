#ifndef sd_fp_h 
#define sd_fp.h
#include <SPI.h>
#include <SD.h> 
#include "Arduino.h"

class FingerPrint
{
  public:
    void saveresistry(int person);
    /*
    void readregistry(int person);
    void saveperson(int person);
    void readperson(int person);    
  private:
    int _pin;
*/
};

#endif
