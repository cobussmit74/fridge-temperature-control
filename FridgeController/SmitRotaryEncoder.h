#ifndef SmitRotaryEncoder_h
#define SmitRotaryEncoder_h

#include "Arduino.h"

class SmitRotaryEncoder
{
  public:
    SmitRotaryEncoder(int pinA, int pinB, int minPos, int maxPos);

    void Tick();
    int Position();
    int NewPosition(); //returns -99 if position has not changed since last call
  private:
    int _pinA;
    int _pinB;
    int _currentPosition;
    int _lastReturnedPosition;
    int _minPosition;
    int _maxPosition;
    int _pinALast;
    int _pinANew;
    int _pinBLast;
    int _pinBNew;
    volatile unsigned long _threshold;
    volatile unsigned long _timePinsSame;
    volatile unsigned long _newTime;
    volatile unsigned long _oldTime;
    bool _changeCought;
};

#endif
