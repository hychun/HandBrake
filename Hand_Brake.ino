/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Gamepad example
  Press a button and demonstrate Gamepad actions

  You can also use Gamepad1,2,3 and 4 as single report.
  This will use 1 endpoint for each gamepad.

  See HID Project documentation for more infos
  https://github.com/NicoHood/HID/wiki/Gamepad-API
*/

#include "HID-Project.h"

#define MAXBUTTON 2

const int pinLed = LED_BUILTIN;
const int pinButton[MAXBUTTON] = {2, 3};   // Pin number by button

void setup() {
  pinMode(pinLed, OUTPUT);
  for (int i = 0; i < MAXBUTTON; i++) {
    pinMode(pinButton[i], INPUT_PULLUP);
  }

  // Sends a clean report to the host. This is important on any Arduino type.
  Gamepad.begin();
}

void loop() {
  // Button detection
  for (int i = 0; i < MAXBUTTON; i++) {
    if (!digitalRead(pinButton[i])) {
      digitalWrite(pinLed, HIGH);

      Gamepad.press(i + 1);
    }
    else if (digitalRead(pinButton[i])) {
      digitalWrite(pinLed, LOW);

      Gamepad.release(i + 1);
    }
  }

  // Axis detection
  int y = analogRead(A2);
  //if (y > 900) y = 1023;    // hardware tune
  //Gamepad.yAxis(map(y, 0, 1023, 0, 32767));
  //Gamepad.ryAxis(map(y, 0, 1023, -32768, 32767));
  Gamepad.zAxis(map(y, 0, 1023, -128, 127));

  /*
      // Press button 1-32
      static uint8_t count = 0;
      count++;
      if (count == 33) {
        Gamepad.releaseAll();
        count = 0;
      }
      else
        Gamepad.press(count);

      // Move x/y Axis to a new position (16bit)
      Gamepad.xAxis(random(0xFFFF));
      Gamepad.yAxis(random(0xFFFF));

      // Go through all dPad positions
      // values: 0-8 (0==centered)
      static uint8_t dpad1 = GAMEPAD_DPAD_CENTERED;
      Gamepad.dPad1(dpad1++);
      if (dpad1 > GAMEPAD_DPAD_UP_LEFT)
        dpad1 = GAMEPAD_DPAD_CENTERED;

      static int8_t dpad2 = GAMEPAD_DPAD_CENTERED;
      Gamepad.dPad2(dpad2--);
      if (dpad2 < GAMEPAD_DPAD_CENTERED)
        dpad2 = GAMEPAD_DPAD_UP_LEFT;
  */
  // Functions above only set the values.
  // This writes the report to the host.
  Gamepad.write();

  // Simple debounce
  delay(1);
  digitalWrite(pinLed, LOW);
}
