# Ultrasonic HC-SR04 with Arduino Uno R4 WiFi

This project demonstrates how to interface an HC-SR04 ultrasonic distance sensor with an Arduino Uno R4 WiFi using PlatformIO. The example firmware triggers the sensor, measures the echo time, and prints the distance (in cm) over the serial monitor.

## Contents
- `src/main.cpp` — Example sketch that reads the HC-SR04 and prints distance to Serial.
- `platformio.ini` — PlatformIO environment configured for `uno_r4_wifi`.

## Hardware
- Arduino Uno R4 WiFi (board used in PlatformIO: `uno_r4_wifi`)
- HC-SR04 ultrasonic sensor
- Breadboard and jumper wires
- USB cable to connect the board to your PC

Recommended: a small logic-level shifter or voltage divider for the Echo pin if your board expects 3.3V I/O. (If your board is 5V tolerant, the HC-SR04 can be connected directly.)

## Wiring
- HC-SR04 VCC -> 5V
- HC-SR04 GND -> GND
- HC-SR04 Trig -> Digital pin D9
- HC-SR04 Echo -> Digital pin D10

(These pin assignments match `src/main.cpp` where `trigPin` is `9` and `echoPin` is `10`.)

## platformio.ini (project settings)
The project contains the following PlatformIO environment:

```ini
[env:uno_r4_wifi]
platform = renesas-ra
board = uno_r4_wifi
framework = arduino
monitor_speed = 9600
```

This config builds for the Arduino Uno R4 WiFi using the Arduino framework and sets the serial monitor baud rate to 9600.

## How it works (code summary)
1. The sketch pulses the Trig pin HIGH for 10 microseconds to start a measurement.
2. The sensor returns an Echo pulse whose length (in microseconds) corresponds to the round-trip time of the ultrasonic wave.
3. The sketch uses `pulseIn(echoPin, HIGH)` to measure the pulse length (microseconds).
4. Distance (cm) is computed with: `distance_cm = duration * 0.034 / 2`.
   - `duration` is in microseconds.
   - `0.034` approximates the speed of sound in cm/µs (34 cm/ms => 0.034 cm/µs).
   - The division by 2 accounts for the round trip (to object and back).
5. The value is printed to Serial at 9600 baud once per second.

## Build & Upload (PlatformIO)
Open a terminal (PowerShell) at the project root and run:

```powershell
# Build and upload to the board using the env from platformio.ini
pio run -e uno_r4_wifi -t upload

# Open the serial monitor (uses monitor_speed from platformio.ini)
pio device monitor -e uno_r4_wifi
```

If PlatformIO cannot auto-detect your port, pass `-p COMx` (replace `COMx` with your serial port) to `pio device monitor`.

## Troubleshooting
- No output on Serial:
  - Confirm USB connection and correct COM port.
  - Verify `monitor_speed` is `9600` or update to match `Serial.begin()`.
- Unexpected or noisy distances:
  - Check wiring (VCC/GND, Trig/Echo pins).
  - Ensure the sensor has a stable 5V supply.
  - If Echo voltage is higher than MCU tolerance, use a level shifter/divider.
- `pulseIn` blocking indefinitely:
  - Consider using the timeout parameter: `pulseIn(echoPin, HIGH, 30000)` to time out after 30 ms.
  - For production code, consider using non-blocking approaches or the `NewPing` library for better performance and reliability.

## Improvements / Next steps
- Average multiple samples to reduce noise.
- Add filtering or median smoothing.
- Use interrupts, a dedicated library (NewPing), or hardware timers for more precise timing and non-blocking measurements.
- Add MQTT/HTTP telemetry using the Uno R4 WiFi's network features.

## License
This project is provided as-is under the MIT license. Copy, modify, and use freely.

---

If you want, I can update the code to add a pulseIn timeout, averaging, or a non-blocking implementation and add example wiring images; tell me which improvement you'd like next.
