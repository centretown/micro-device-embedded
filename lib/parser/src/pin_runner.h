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
#else
    if (args()->mode() == 'o') {
      printf("digitalWrite(%d, %d);\n", args()->pin(), args()->value());
    } else if (args()->signal() == 'a') {
      printf("args()->set_value(analogRead(%d));\n", args()->pin());
    } else {
      printf("args()->set_value(digitalRead(%d));\n", args()->pin());
    }
#endif  // ARDUINO
  }
};
