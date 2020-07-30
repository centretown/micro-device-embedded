// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <stdio.h>
#endif  // ARDUINO

#include "pin_parser.h"  // NOLINT
#include "runner.h"      // NOLINT

class PinRunner : public Runner<Pin> {
 public:
  explicit PinRunner(Pin* pin, Writer* writer) : Runner<Pin>(pin, writer) {}
  ~PinRunner() {}

  void Run() override {
    auto pin = this->args();
#if defined(ARDUINO)
    if (pin->mode() == 'o') {
      digitalWrite(pin->pin(), pin->value());
    } else if (pin->signal() == 'a') {
      pin->set_value(analogRead(pin->pin()));
    } else {
      pin->set_value(digitalRead(pin->pin()));
    }
#else
    if (pin->mode() == 'o') {
      printf("digitalWrite(%d, %d);\n", pin->pin(), pin->value());
    } else if (pin->signal() == 'a') {
      printf("pin->set_value(analogRead(%d));\n", pin->pin());
    } else {
      printf("pin->set_value(digitalRead(%d));\n", pin->pin());
    }
#endif  // ARDUINO
  }
};
