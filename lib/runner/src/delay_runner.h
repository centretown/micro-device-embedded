// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#if defined(ARDUINO)
#pragma once

#include <Arduino.h>

#include "delay_parser.h"  // NOLINT
#include "runner.h"        // NOLINT

class DelayRunner : public Runner<DelayParser> {
 public:
  explicit DelayRunner(DelayParser* parser) : Runner(parser) {}
  ~DelayRunner() {}

  void Run() override {
    if (parser()->ok()) delay(parser()->duration());
  }
};
#endif  // ARDUINO