#include "Arduino.h"
#include "SmitThermistor.h"

float lastReturned = 0;
float currentAccumelator = 0;
int numberReadingTaken = 0;

SmitThermistor::SmitThermistor(int analogPin)
{
  _analogPin = analogPin;
  
  pinMode (_analogPin, INPUT);
}

float SmitThermistor::Read()
{
  currentAccumelator += analogRead(_analogPin);
  numberReadingTaken++;
  if (numberReadingTaken < 100)
  {
    return lastReturned;
  }
  
  float reading = currentAccumelator / numberReadingTaken;
  currentAccumelator = 0;
  numberReadingTaken = 0;
 
  reading = 1023 / reading - 1;
  reading = SERIESRESISTOR / reading;
 
  float steinhart;
  steinhart = reading / THERMISTORNOMINAL;
  steinhart = log(steinhart);            
  steinhart /= BCOEFFICIENT;              
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);
  steinhart = 1.0 / steinhart;              
  steinhart -= 273.15;                    

  lastReturned = steinhart;
  return steinhart;
}
