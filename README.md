# Smart Digital Bell System with Timetable Using Arduino

This project is a Tinkercad-based simulation of a smart digital bell system designed to automate school bell operations using Arduino.

## Project Description
The system uses an Arduino Uno to control a digital bell based on a predefined weekday timetable. A DIP switch is used to select the day (Monday to Friday), and the corresponding schedule runs automatically. A 16×2 LCD displays the selected day and current period, while a buzzer rings at the end of each period, break, and lunch. A STOP switch is provided for emergency control.

## Features
- Automatic bell system based on timetable
- Day selection using DIP switch
- 16×2 LCD display for day and period
- Buzzer for bell indication
- Emergency STOP switch
- Simulated timing for class, break, and lunch

## Components Used
- Arduino Uno
- 16×2 LCD Display
- Buzzer
- DIP Switch
- Push Button (STOP)
- Resistors
- Connecting Wires

## Software Used
- Tinkercad Circuits
- Arduino IDE (for code development)

## Working Principle
The Arduino reads the selected day from the DIP switch and follows the predefined timetable for that day. Each period runs for a fixed duration, after which the buzzer rings automatically. The LCD continuously displays the current day and period information.

## License
This project is licensed under the MIT License and is intended for educational purposes.
