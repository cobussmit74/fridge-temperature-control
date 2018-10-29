# fridge-temperature-control
An arduino application that monitors temperature using a thermistor and switches a relay on/off based on the user selected target temperature

## Assumed pins
### TM1637 Display
* CLK = D4
* DIO = D5
  
### Temprature Select Rotary Encoder
* D2 and D3

By default the selectable range is from -15&deg;C to 15&deg;C
  
### Thermistor
* A0
  
### Relay control
* D6
