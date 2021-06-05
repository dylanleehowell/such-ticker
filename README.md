# such-view
A dogecoin ticker controlled by an ESP8266. Why? Because 2021.

## Overview
An ESP8266 retrieves the latest dogecoin price in USD and displays it on a 16X2 LCD.

## Parts List
* NodeMCU ESP8266 Breakout Board
  * Programming interface: Serial over USB
  * Input voltage: 5V
  * Logic level: 3V3
* Grove - LCD RGB Backlight 
  * Input Voltage: 5V
  * Interface: I2C
  * Resolution: 16X2 characters

## Prerequisites
* Arduino IDE is installed
* ESP8266 boards are installed via Boards Manager
* Libraries are installed:
  * [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
  * [Grove - LCD RGB Backlight](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight)
  * [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
  * [ESP8266HTTPClient](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient)

