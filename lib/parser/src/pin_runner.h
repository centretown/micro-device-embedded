// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#if defined(ARDUINO)
#include <Arduino.h>
#endif

#include "pin_parser.h"  // NOLINT
#include "runner.h"      // NOLINT

class PinRunner : public Runner<Pin> {
 public:
  explicit PinRunner(Pin* args) : Runner<Pin>(args) {}
  ~PinRunner() {}

  void Run() override {
#if defined(ARDUINO)
    if (args()->mode() == 'o') {
      digitalWrite(args()->pin(), args()->value());
    } else if (args()->signal() == 'a') {
      args()->set_value(analogRead(args()->pin()));
    } else {
      args()->set_value(digitalRead(args()->pin()));
    }
#endif  // ARDUINO
  }
};
