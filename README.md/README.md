# Smart Irrigation System

An ESP32 prototype sketch intended to water two pots using a soil-moisture sensor, a servo to select a pot, and an active-low relay for a pump.

## Hardware and pin mapping

- ESP32 development board
- Soil-moisture sensor analog output: GPIO 33
- Active-low pump relay: GPIO 4
- Servo signal: GPIO 18
- External pump power supply appropriate for the pump and relay

Do not power a pump or servo directly from an ESP32 GPIO. Use suitable driver hardware, common ground where required, and keep water away from exposed electronics.

## Arduino dependency

Install the **ESP32Servo** library and select the appropriate ESP32 board in Arduino IDE.

## Intended behavior

The sketch defines target moisture levels of 70% and 80% for two pots, maps ADC readings from approximately 4000 (dry) to 2500 (wet), moves the servo to each pot's configured angle, and runs the pump until the target is reached. Adjust the calibration and target values for your sensor and soil.

## Important: source needs cleanup before compiling

`SSS.ino` currently contains duplicate definitions of `getMoisture()`, `pumpON()`, `pumpOFF()`, and `waterPot()`. The later set also refers to `rawValue`, `moisture`, and `pumpStatus`, which are not declared in the file. The sketch will need those issues resolved before it can compile; the README documents the file as uploaded and does not silently alter it.

The pump loop has no timeout, so test with care and ensure the pump cannot run indefinitely if the sensor reading fails.
