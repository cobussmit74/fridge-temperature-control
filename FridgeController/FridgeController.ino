#include <Arduino.h>
#include "SmitThermistor.h"
#include "SmitRotaryEncoder.h"
#include "TM1637Display.h"

#define newTempDisplayMillis 5000

TM1637Display ledDisplay(4,5);
SmitRotaryEncoder tempSelect(2, 3, -15, 15);
SmitThermistor temp(A0);
int _fridgeControlPin = 6;
float _selectedTemp = 0;
unsigned long oldTime = 0;
unsigned long totalTimeDisplayed = 0;

void setup() {
  Serial.begin (9600);
  
  pinMode (_fridgeControlPin, OUTPUT);
  digitalWrite(_fridgeControlPin, LOW);

  ledDisplay.setBrightness(0x0f);
}

void loop() {
  float currentTemp = temp.Read();
  
  displayCurrentTempOnScreen(currentTemp);
  
  checkForNewSelectedTemp();

  switchFridge(currentTemp);
}

void displayCurrentTempOnScreen(float currentTemp)
{
  long newTime = millis();
  unsigned long elapsedtime = newTime - oldTime;
  
  if (totalTimeDisplayed != -1)
  {
    totalTimeDisplayed = totalTimeDisplayed + elapsedtime;
    if (totalTimeDisplayed >= newTempDisplayMillis)
    {
      totalTimeDisplayed = -1;
    }
  } 
  else
  {
    displayTemperature((int)currentTemp);
  }
  
  oldTime = newTime;
}

void checkForNewSelectedTemp()
{
  tempSelect.Tick();
  
  int newTemp;
  newTemp = tempSelect.NewPosition();
  if (newTemp != -99)
  {
    _selectedTemp = newTemp;
    totalTimeDisplayed = 0;
    displayTemperature(newTemp);
  }
}

void displayTemperature(int newTemp)
{
  bool isNeg = newTemp < 0;
  if (isNeg)
  {
    newTemp = newTemp * -1;
  }
  
  ledDisplay.showNumberDec(newTemp);

  if (isNeg)
  {
    int positionOfSign = 2;
    if (newTemp >= 10) positionOfSign = 1;
    uint8_t data[]= {0b01000000};
    ledDisplay.setSegments(data, 1, positionOfSign);
  }
}

void switchFridge(float currentTemp)
{
  float selectedTempMin = _selectedTemp + 0.2;
  float selectedTempMax = _selectedTemp + 0.8;
  if (currentTemp < selectedTempMin)
  {
    digitalWrite(_fridgeControlPin, LOW);
  }
  else if (currentTemp > selectedTempMax)
  {
    digitalWrite(_fridgeControlPin, HIGH);
  }
}
