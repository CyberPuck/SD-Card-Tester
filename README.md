# SD Card Tester
This simple library is for testing the status of a SD card.  Current use case is for verifying if a SD card is encrypted.  If the card is encrypted the card type will be detected but it will not be able to enumerate over the volume.

# Using the application
Use the following steps:
1. Connect up the wires, follow [the pin configuration section](#pin-configuration) for wire connection details.
2. Compile the software.
3. Load the software onto the Arduino Uno.
4. Connect a serial terminal (9600 baud) to the Arduino Uno.
5. If you haven't already plug in the SD Card.

SD Card data should be printed out on the serial terminal.

# Physcial Configuration
## Hardware Setup
This test library is using a [Sparkfun uSD Shifting board](https://www.sparkfun.com/products/13743) to hold the SD Card and break out the pins, the microcontroller is an [Arduino Uno R2](https://store.arduino.cc/usa/arduino-uno-rev3).  Newer Arduino Uno boards like the R3 should work as well.

A breadboard is used to connect the uSD board and Arduino Uno together.  A power status LED is also connected for debugging.

## Pin Configuration
Due to the SPI pins already being selected for the SD.h library, the same pin layout is used in this example.  An extra pin provided by the breakout board is the CD (Chip Detect pin).

|Name|Ardunio Pin|uSD Pin|
|----|-----------|-------|
|Supply Voltage|5V|VCC|
|Chip Select|8|CS|
|Data In|11|DI|
|Clock|13|SCK|
|Data Out|12|DO|
|Chip Detect|9|CD|
|Ground|GND|GND|

# Software Configuration
## Third Party Libraries
All third party libraries are provided by the [Arduino group](https://github.com/arduino-libraries/).  Currently the following are used:
- SPI.h
- SD.h