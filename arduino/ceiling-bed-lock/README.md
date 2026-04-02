# Ceiling Bed Lock Controller

Arduino controller for servo-actuated deadbolt locks on a ceiling bed. These locks act as a safety mechanism — when the bed is stored up in the ceiling, the deadbolts engage to prevent the bed from falling if a cable snaps.

## How It Works

Two servo motors drive two deadbolt latches. Two momentary switches control the lock direction:

| Input       | Pin | Action                          |
|-------------|-----|---------------------------------|
| Left switch | D7  | Rotate servos to locked (120°)  |
| Right switch| D8  | Rotate servos to unlocked (60°) |

Both servos start at the neutral position (90°) on power-up.

## Wiring

| Component   | Arduino Pin |
|-------------|-------------|
| Servo 1     | D9          |
| Servo 2     | D10         |
| Switch Left | D7 (INPUT_PULLUP) |
| Switch Right| D8 (INPUT_PULLUP) |

Switches are wired to ground (active LOW) using the internal pull-up resistors.

## Dependencies

- [Servo](https://www.arduino.cc/reference/en/libraries/servo/) (built-in Arduino library)

## Upload

Open `ceiling-bed-lock.ino` in the Arduino IDE and upload to your board.
