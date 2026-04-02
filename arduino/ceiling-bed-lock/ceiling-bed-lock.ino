#include <Servo.h>

Servo latch1;
Servo latch2;

const int SERVO1_PIN = 9;
const int SERVO2_PIN = 10;
const int SW_LEFT    = 7;
const int SW_RIGHT   = 8;

const int ANGLE_MID   = 90;
const int ANGLE_LEFT  = ANGLE_MID + 30;
const int ANGLE_RIGHT = ANGLE_MID - 30;

const unsigned long DEBOUNCE_MS = 50;

int currentAngle = ANGLE_MID;
int lastSwLeft   = HIGH;
int lastSwRight  = HIGH;

void moveToAngle(int angle) {
  if (angle != currentAngle) {
    currentAngle = angle;
    latch1.write(currentAngle);
    latch2.write(currentAngle);
  }
}

void moveToAngleSlow(int target) {
  if (target != currentAngle) {
    int step = (target > currentAngle) ? 1 : -1;
    while (currentAngle != target) {
      currentAngle += step;
      latch1.write(currentAngle);
      latch2.write(currentAngle);
      delay(15);
    }
  }
}

void setup() {
  latch1.attach(SERVO1_PIN);
  latch2.attach(SERVO2_PIN);
  pinMode(SW_LEFT, INPUT_PULLUP);
  pinMode(SW_RIGHT, INPUT_PULLUP);
  latch1.write(ANGLE_MID);
  latch2.write(ANGLE_MID);
}

void loop() {
  int swLeft  = digitalRead(SW_LEFT);
  int swRight = digitalRead(SW_RIGHT);

  if (swLeft == LOW && lastSwLeft == HIGH) {
    delay(DEBOUNCE_MS);
    moveToAngle(ANGLE_LEFT);
  }

  if (swRight == LOW && lastSwRight == HIGH) {
    delay(DEBOUNCE_MS);
    moveToAngle(ANGLE_RIGHT);
  }

  lastSwLeft  = swLeft;
  lastSwRight = swRight;

  delay(20);
}
