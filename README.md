# ESP32 Automated Pre-Workout Dispenser and Mixer

An ESP32-based embedded system that measures, dispenses, and mixes pre-workout powder and water using load-cell feedback.

This project was developed as the final project for ECE 2360. The completed prototype combined sensor integration, motor control, circuit fabrication, embedded programming, and user-interface components into an automated dispensing system.

## Project Overview

The system was designed to automate the process of preparing a pre-workout drink.

Users selected either water or powder using physical buttons. The ESP32 then activated the corresponding dispensing mechanism while continuously monitoring weight through a load cell and HX711 amplifier.

Once the measured weight reached the configured target, the ESP32 stopped the pump or dispensing motor. An LCD displayed status updates throughout the process, and a separate motor was used to mix the completed solution.

## Final Prototype

![Completed pre-workout dispenser](images/prototype.jpg =200x200)

## System Features

- ESP32-based embedded control system
- Weight-based water and powder dispensing
- Load-cell measurements through an HX711 amplifier
- Automatic actuator shutoff after reaching a configured target
- Water pump controlled through a motor driver
- Motor-driven powder-dispensing mechanism
- Mixing motor for preparing the completed solution
- Two-button user interface
- 16×2 I²C LCD for system status updates
- External battery supply for the pump and motors
- Two custom soldered perfboard circuits

## How It Works

1. The user selects water or powder using one of two physical buttons.
2. The ESP32 updates the LCD with the selected operation.
3. The load cell is tared to establish a zero-weight reference.
4. The ESP32 activates the corresponding pump or dispensing motor.
5. Weight measurements are continuously collected through the HX711 module.
6. The selected actuator stops after the measured weight reaches its configured target.
7. The LCD returns to the default system display.
8. A mixing motor combines the dispensed powder and water.

## Hardware

The prototype integrated the following components:

- ESP32 microcontroller
- Load cell
- HX711 load-cell amplifier
- 16×2 I²C LCD
- Two push buttons
- Water pump
- Powder-dispensing motor
- Mixing motor
- L293D motor driver
- External battery supply
- Two soldered perfboards
- Supporting resistors, wiring, and connectors

## Circuit Construction

The control and power circuits were soldered across two separate perfboards. The boards connected the ESP32 to the load cell, LCD, buttons, motor driver, pump, dispensing motor, and external power supply.

Separating the circuitry across two boards helped organize the control electronics and higher-current motor components.


![](images/soldering_perfboard.jpg =200x200)

## Software

The system was programmed in C++ using the Arduino framework.

The program uses:

- `LiquidCrystal_I2C` for LCD communication
- `HX711_ADC` for load-cell measurements
- GPIO inputs for physical button controls
- GPIO outputs for pump and motor-driver control
- Feedback-based dispensing logic
- Serial output for testing and debugging

The water and powder dispensing functions tare the scale, activate the appropriate actuator, continuously read the load cell, and stop the actuator once the configured target weight is reached.

## Feedback-Based Dispensing

Thee project uses sensor feedback to determine when an actuator should stop.

```text
Button Input
     ↓
Tare Load Cell
     ↓
Start Pump or Motor
     ↓
Continuously Measure Weight
     ↓
Target Weight Reached?
     ↓
Stop Actuator
```

![](images/display_idle.jpg =100x100)
![](images/display_powder.jpg =200x200)
![](images/display_water.jpg =200x200)

This approach helps account for variations in pump flow, motor speed, and the amount of material being dispensed.

## My Contributions

- Developed the embedded C++ logic for the load cell, LCD, buttons, water pump, and dispensing motor
- Implemented weight-based control that stopped each actuator after reaching a configured target
- Calibrated and integrated the load cell using an HX711 amplifier
- Designed and soldered the control and power circuitry across two perfboards
- Integrated the ESP32, motor driver, battery, pump, motors, display, sensor, and physical controls
- Tested and debugged the individual hardware and software components
- Collaborated with a project partner on final system assembly and testing

## Team Collaboration

This project was completed with a project partner.

I developed the individual code segments for the system components and designed and soldered the supporting circuitry. My partner combined the individual software segments into the final integrated program. We collaborated on system assembly, troubleshooting, and final testing.

## Technologies and Skills

- ESP32
- C++
- Arduino
- Embedded systems
- Circuit design
- Soldering
- Perfboard fabrication
- Hardware-software integration

## Repository Structure

```text
esp32-pre-workout-dispenser/
├── README.md
├── src/
│   └── pre_workout_dispenser.ino
└── images/
    ├── display_idle.jpg
    ├── display_powder.jpg
    ├── display_water.jpg
    ├── prototype.jpg
    ├── prototype_2.jpg
    └── soldering_perfboard.jpg

```

## Required Arduino Libraries

The following libraries are required:

- `LiquidCrystal_I2C`
- `HX711_ADC`

They can be installed through the Arduino IDE Library Manager.

## Running the Project

1. Open `src/pre_workout_dispenser.ino` in the Arduino IDE.
2. Install the required libraries.
3. Select the appropriate ESP32 board.
4. Connect the ESP32 through USB.
5. Verify the GPIO pin assignments for the connected hardware.
6. Update the load-cell calibration factor if necessary.
7. Upload the program to the ESP32.
8. Open the Serial Monitor at `115200` baud for debugging information.

## Project Context

This project was created as the final project for ECE 2360. It was developed as an educational prototype and is not intended for commercial food or supplement dispensing.
