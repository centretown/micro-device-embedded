// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#if defined(ARDUINO)
#pragma once

#include <Arduino.h>

#include "pin_parser.h"  // NOLINT
#include "runner.h"      // NOLINT

class PinRunner : public Runner<PinParser> {
 public:
  explicit PinRunner(PinParser* parser) : Runner(parser) {}
  ~PinRunner() {}

  void Run() override {
    if (parser()->ok()) {
      if (parser()->mode() == 'o') {
        digitalWrite(parser()->pin(), parser()->value());
      } else if (parser()->signal() == 'a') {
        parser()->set_value(analogRead(parser()->pin()));
      } else {
        parser()->set_value(digitalRead(parser()->pin()));
      }
    }
  }
};
#endif  // ARDUINO
