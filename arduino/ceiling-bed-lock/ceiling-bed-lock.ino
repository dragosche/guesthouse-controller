#include <Servo.h>

Servo servoToeLeft;
Servo servoToeRight;
Servo servoHeadLeft;
Servo servoHeadRight;

const int PIN_TOE_LEFT   = 9;
const int PIN_TOE_RIGHT  = 10;
const int PIN_HEAD_LEFT  = 11;
const int PIN_HEAD_RIGHT = 12;

const int SW_OPEN  = 7;
const int SW_CLOSE = 8;

// Adjust per corner to match physical mounting orientation
const int TOE_LEFT_OPEN    = 9;
const int TOE_LEFT_CLOSE   = 105;
const int TOE_RIGHT_OPEN   = 54;
const int TOE_RIGHT_CLOSE  = 140;
const int HEAD_LEFT_OPEN   = 50;
const int HEAD_LEFT_CLOSE  = 130;
const int HEAD_RIGHT_OPEN  = 150;
const int HEAD_RIGHT_CLOSE = 60;

const unsigned long DEBOUNCE_MS = 50;

int lastSwOpen  = HIGH;
int lastSwClose = HIGH;

void openAll() {
  servoToeLeft.write(TOE_LEFT_OPEN);
  servoToeRight.write(TOE_RIGHT_OPEN);
  servoHeadLeft.write(HEAD_LEFT_OPEN);
  servoHeadRight.write(HEAD_RIGHT_OPEN);
}

void closeAll() {
  servoToeLeft.write(TOE_LEFT_CLOSE);
  servoToeRight.write(TOE_RIGHT_CLOSE);
  servoHeadLeft.write(HEAD_LEFT_CLOSE);
  servoHeadRight.write(HEAD_RIGHT_CLOSE);
}

void setup() {
  servoToeLeft.attach(PIN_TOE_LEFT);
  servoToeRight.attach(PIN_TOE_RIGHT);
  servoHeadLeft.attach(PIN_HEAD_LEFT);
  servoHeadRight.attach(PIN_HEAD_RIGHT);
  pinMode(SW_OPEN, INPUT_PULLUP);
  pinMode(SW_CLOSE, INPUT_PULLUP);
  openAll();
}

void loop() {
  int swOpen  = digitalRead(SW_OPEN);
  int swClose = digitalRead(SW_CLOSE);

  if (swOpen == LOW && lastSwOpen == HIGH) {
    delay(DEBOUNCE_MS);
    openAll();
  }

  if (swClose == LOW && lastSwClose == HIGH) {
    delay(DEBOUNCE_MS);
    closeAll();
  }

  lastSwOpen  = swOpen;
  lastSwClose = swClose;

  delay(20);
}
