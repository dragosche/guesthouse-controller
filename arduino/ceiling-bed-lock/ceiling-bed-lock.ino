#include <Servo.h>

const int SW_OPEN  = 7;
const int SW_CLOSE = 8;

// Set true to calibrate a single servo via Serial: type an angle (0-180) and press Enter
const bool DISCOVERY_MODE = true;
const int  DISCOVERY_CORNER = 0;  // index into corners[] to calibrate

const unsigned long DEBOUNCE_MS = 50;

struct Corner {
  int servoIndex;
  int pin;
  int openPush;
  int openRest;
  int closePush;
  int closeRest;
};

// Indices match corners[]
enum { TOE_LEFT, TOE_RIGHT, HEAD_LEFT, HEAD_RIGHT, CORNER_COUNT };

Servo servos[CORNER_COUNT];

Corner corners[CORNER_COUNT] = {
  //               pin   openPush openRest closePush closeRest
  { TOE_LEFT,    9,    0,       5,       168,      150 },
  { TOE_RIGHT,  10,   54,      54,       140,      140 },  // placeholder
  { HEAD_LEFT,  11,   50,      50,       130,      130 },  // placeholder
  { HEAD_RIGHT, 12,  150,     150,        60,       60 },  // placeholder
};

void moveAndDetach(Corner &c, int push, int rest) {
  servos[c.servoIndex].attach(c.pin);
  servos[c.servoIndex].write(push);
  delay(600);
  servos[c.servoIndex].write(rest);
  delay(300);
  servos[c.servoIndex].detach();
}

void openAll() {
  for (int i = 0; i < CORNER_COUNT; i++)
    moveAndDetach(corners[i], corners[i].openPush, corners[i].openRest);
}

void closeAll() {
  for (int i = 0; i < CORNER_COUNT; i++)
    moveAndDetach(corners[i], corners[i].closePush, corners[i].closeRest);
}

void setup() {
  pinMode(SW_OPEN, INPUT_PULLUP);
  pinMode(SW_CLOSE, INPUT_PULLUP);

  if (DISCOVERY_MODE) {
    servos[DISCOVERY_CORNER].attach(corners[DISCOVERY_CORNER].pin);
    Serial.begin(9600);
    Serial.println("CALIBRATION: type an angle (0-180) and press Enter");
  } else {
    openAll();
  }
}

int lastSwOpen  = HIGH;
int lastSwClose = HIGH;

void loop() {
  if (DISCOVERY_MODE && Serial.available()) {
    int angle = Serial.parseInt();
    while (Serial.available()) Serial.read();
    if (angle >= 0 && angle <= 180) {
      servos[DISCOVERY_CORNER].write(angle);
      Serial.print("corner["); Serial.print(DISCOVERY_CORNER); Serial.print("] -> ");
      Serial.println(angle);
    }
  }

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
