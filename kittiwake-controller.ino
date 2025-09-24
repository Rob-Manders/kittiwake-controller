#include <Joystick.h>

const int deadzone = 5;
const int minAxisRange = 0;
const int maxAxisRange = 1023;
const int axisCentre = maxAxisRange / 2;

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
const int joystickButtonValue = keyCount * 2;

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

  controller.setXAxisRange(minAxisRange, maxAxisRange);
  controller.setYAxisRange(maxAxisRange, minAxisRange);

  controller.begin();
}

void loop() {
  for (int i = 0; i < keyCount; i++) {
    int button = getButton(i);

    if (digitalRead(i) == LOW) {
      controller.pressButton(button);
    } else {
      controller.releaseButton(button);
    }
  }

  if (digitalRead(joystickButtonPin) == LOW) {
    controller.pressButton(joystickButtonValue);
  } else {
    controller.releaseButton(joystickButtonValue);
  }

  setXAxis();
  setYAxis();

  delay(10);
}

void setXAxis() {
  int value = analogRead(xAxis);

  if (isDeadzone(value)) {
    controller.setXAxis(axisCentre);
    return;
  }

  controller.setXAxis(value);
}

void setYAxis() {
  int value = analogRead(yAxis);

  if (isDeadzone(value)) {
    controller.setYAxis(axisCentre);
    return;
  }

  controller.setYAxis(value);
}

bool isDeadzone(int axisValue) {
  return (axisValue > axisCentre - deadzone && axisValue < axisCentre + 10);
}

int getButton(int key) {
  if (digitalRead(keyShift) == LOW) {
    return key + keyCount;
  }

  return key;
}
