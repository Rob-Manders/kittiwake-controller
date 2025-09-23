#include <Joystick.h>

const int keyCount = 14;

const int xAxis = A3;
const int yAxis = A2;

const int key01 = 1;
const int key02 = 0;
const int key03 = 2;
const int key04 = 3;
const int key05 = 4;
const int key06 = 5;
const int key07 = 6;
const int key08 = 7;
const int key09 = 8;
const int key10 = 9;
const int key11 = 10;
const int key12 = 16;
const int key13 = 14;
const int key14 = 15;

const int keyShift = 18;

const int joystickButtonPin   = 19;
const int joystickButtonValue = keyCount * 2 + 1;

const int buttonKeys[keyCount] = {
  key01, key02, key03, key04, key05,
  key06, key07, key08, key09, key10,
  key11, key12, key13, key14
};

Joystick_ controller(
  JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_GAMEPAD,
  29, 0,                  // Button Count, Hat Switch Count
  true,  true,  false,    // X and Y, but no Z Axis
  false, false, false,    // No Rx, Ry, or Rz
  false, false,           // No rudder or throttle
  false, false, false     // No accelerator, brake, or steering
);

void setup() {
  for (int i = 0; i < keyCount; i++) {
    pinMode(buttonKeys[i], INPUT_PULLUP);
  }

  pinMode(keyShift, INPUT_PULLUP);
  pinMode(joystickButtonPin, INPUT_PULLUP);

  controller.setXAxisRange(1023, 0);
  controller.setYAxisRange(0, 1023);

  controller.begin();
}

void loop() {
  for (int i = 0; i < keyCount; i++) {
    if (digitalRead(i) == LOW) {
      controller.pressButton(getButton(i));
    }
  }

  if (digitalRead(joystickButtonPin) == LOW) {
    controller.pressButton(joystickButtonValue);
  }

  controller.setXAxis(analogRead(xAxis));
  controller.setYAxis(analogRead(yAxis));

  delay(20);
}

int getButton(int key) {
  if (digitalRead(keyShift) == LOW) {
    return key + keyCount;
  }

  return key;
}
