// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#if defined(ARDUINO)
#include <Arduino.h>
#endif  // ARDUINO

#include "delay.h"   // NOLINT
#include "runner.h"  // NOLINT

class DelayRunner : public Runner<Delay> {
 public:
  explicit DelayRunner(Delay* args) : Runner(args) {}
  ~DelayRunner() {}
  void Run() override {
#if defined(ARDUINO)
    delay(args()->duration());
#endif  // ARDUINO
  }
};
