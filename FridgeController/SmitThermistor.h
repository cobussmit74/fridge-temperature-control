#ifndef SmitThermistor_h
#define SmitThermistor_h

#include "Arduino.h"

#define THERMISTORNOMINAL 10000      
#define TEMPERATURENOMINAL 25   
#define BCOEFFICIENT 3950
#define SERIESRESISTOR 10000

class SmitThermistor
{
  public:
    SmitThermistor(int analogPin);

    float Read();
  private:
  int _analogPin;
};

#endif
