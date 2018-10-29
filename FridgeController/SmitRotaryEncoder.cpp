#include "Arduino.h"
#include "SmitRotaryEncoder.h"

SmitRotaryEncoder::SmitRotaryEncoder(int pinA, int pinB, int minPos, int maxPos)
{
  _pinA = pinA;
  _pinB = pinB;
  _minPosition = minPos;
  _maxPosition = maxPos;
  _currentPosition = 0;
  _lastReturnedPosition = _currentPosition;

  _pinALast = HIGH;
  _pinANew = HIGH;
  _pinBNew = HIGH;
  _timePinsSame = 0;
  _newTime = 0;
  _oldTime = micros();
  _changeCought = false;

  _threshold = 1000;
  
  pinMode (_pinA, INPUT_PULLUP);
  pinMode (_pinB, INPUT_PULLUP);
}

void SmitRotaryEncoder::Tick()
{
  _pinANew = digitalRead(_pinA);
  _pinBNew = digitalRead(_pinB);

  _newTime = micros();
  
  if (_pinALast != _pinANew)
  {
    _timePinsSame = 0;
    _changeCought = false;
  }
  else if (_changeCought == false)
  {
    _timePinsSame = _timePinsSame + (_newTime - _oldTime);

    if (_timePinsSame >= _threshold)
    {
      _changeCought = true;

      if (_pinANew == LOW)
      {
        if (_pinBNew == LOW)
        {
          if (_currentPosition < _maxPosition)
          {
            _currentPosition++;
          }
        }
        else
        {
          if (_currentPosition > _minPosition)
          {
            _currentPosition--;
          }
        }
      }
    }
  }

  _pinALast = _pinANew;
  _oldTime = _newTime;  
}

int SmitRotaryEncoder::Position()
{
  return _currentPosition;
}

int SmitRotaryEncoder::NewPosition()
{
  if (_lastReturnedPosition == _currentPosition)
  {
    return -99;
  }
  else
  {
    _lastReturnedPosition = _currentPosition;
    return _lastReturnedPosition;
  }
}
