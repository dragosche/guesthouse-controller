# Guesthouse Controller

## Hardware

- **Board**: Arduino Mega 2560
- **Ceiling bed**: Queen size, stored at 7ft (ceiling), lowers to 16in from floor
- **Sensors**: LD2410C mmWave 24GHz human presence radar (3 units available)

## Pin Assignments

| Component                  | Pin       | Direction |
|----------------------------|-----------|-----------|
| Servo TOE_LEFT (latch)     | D9        | Output    |
| Servo TOE_RIGHT (latch)    | D10       | Output    |
| Servo HEAD_LEFT (latch)    | D11       | Output    |
| Servo HEAD_RIGHT (latch)   | D12       | Output    |
| Switch Open                | D7        | Input (PULLUP) |
| Switch Close               | D8        | Input (PULLUP) |
| LD2410C OUT                | D2        | Input (10kΩ pull-down to GND) |
| LD2410C TX                 | D19 (RX1) | Input (Serial1 hardware UART) |
| LD2410C RX                 | D18 (TX1) | Output (Serial1 hardware UART) |

## Guidelines

- Safety-critical embedded code — prefer simplicity and reliability over cleverness.
- Fail-closed design: if a sensor fails, default to blocking bed movement.
