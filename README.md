# Smart Dustbin Monitoring System

A smart dustbin project built using Arduino that detects garbage level using an ultrasonic sensor and displays the current status on a MAX7219 LED matrix display. This system helps monitor whether the dustbin is full or not, making waste management more efficient and reducing overflow problems.

## Project Overview

This project uses a low-cost and easy-to-build setup to monitor waste levels in real time. The ultrasonic sensor measures the distance between the sensor and the waste inside the bin. Based on that measurement, the Arduino decides whether the bin is full or not and displays the result on the LED matrix.

## Features

- Real-time dustbin fill level detection
- Ultrasonic distance measurement
- Full/not-full status display
- Simple, low-cost hardware design
- Easy to build and modify
- Suitable for homes, offices, campuses, and smart city applications

## Components Used

- Arduino UNO
- HC-SR04 Ultrasonic Sensor
- MAX7219 8x8 LED Dot Matrix Display
- Breadboard
- Jumper wires
- USB cable
- 5V power supply

## Working Principle

The ultrasonic sensor emits a pulse and waits for the echo to return. The Arduino calculates the time difference and converts it to distance using the formula:

Distance = (Speed of Sound × Time) / 2

The measured distance is compared with a predefined threshold. If the waste is within the threshold range, the dustbin is considered full and the display shows:

- DUSTBIN FULL

Otherwise, the display shows:

- NOT FULL

## Hardware Connection

| Component | Arduino Pin |
|-----------|------------|
| Ultrasonic TRIG | 9 |
| Ultrasonic ECHO | 8 |
| MAX7219 CS | 10 |
| MAX7219 DIN | 11 |
| MAX7219 CLK | 13 |
| VCC | 5V |
| GND | GND |

> Note: The code uses SPI-based communication for the MAX7219 display. Make sure the display is connected correctly to the SPI pins and powered properly.

## Required Libraries

Before uploading the code, install the following Arduino libraries:

- MD_Parola
- MD_MAX72xx

To install libraries in the Arduino IDE:

1. Open Arduino IDE
2. Go to Sketch > Include Library > Manage Libraries
3. Search for MD_Parola and MD_MAX72xx
4. Click Install

## File Structure

- smartdustbin.ino - Main Arduino program
- README.md - Project documentation

## Code Description

The Arduino sketch does the following:

1. Initializes the ultrasonic sensor and the LED matrix display
2. Shows a startup message: SMART DUSTBIN
3. Measures the distance repeatedly in the loop
4. Compares the distance with the full threshold
5. Displays either DUSTBIN FULL or NOT FULL on the LED matrix

## Threshold Value

The project uses this threshold:

```cpp
#define FULL_DISTANCE 15   // cm
```

If the distance is less than or equal to 15 cm, the dustbin is considered full.

## Upload Instructions

1. Connect the Arduino to your computer using a USB cable.
2. Open the smartdustbin.ino file in the Arduino IDE.
3. Select the correct board and COM port.
4. Click Upload.
5. Open the Serial Monitor to view the measured distance values.

## Example Output

```text
Distance: 12.50 cm
Distance: 14.20 cm
Distance: 18.30 cm
```

The LED display will update based on the measured readings.

## Applications

This project can be used in:

- Smart homes
- Offices and campuses
- Public parks
- Waste collection systems
- Smart city projects
- Educational electronics projects

## Future Enhancements

Possible improvements include:

- GSM or Wi-Fi module for remote alerts
- Mobile app integration
- Real-time cloud monitoring
- Solar-powered smart bin
- Automatic lid opening mechanism
- Sensor data logging

## Conclusion

This smart dustbin prototype demonstrates a practical and low-cost solution for monitoring waste levels. It is an excellent beginner-friendly Arduino project with real-world application in smart waste management systems.

## License

This project is open for educational and personal use.

## Author

Smart Dustbin Monitoring System using Arduino and Ultrasonic Sensor