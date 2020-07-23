// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#if defined(ARDUINO)
#pragma once

#include <Arduino.h>

#include "mode_parser.h"  // NOLINT
#include "runner.h"       // NOLINT

class ModeRunner : public Runner<ModeParser> {
 public:
  explicit ModeRunner(ModeParser* parser) : Runner(parser) {}
  ~ModeRunner() {}

  void Run() override {
    if (parser()->ok()) {
      if (parser()->mode() == 'o') {
        pinMode(parser()->pin(), OUTPUT);
      } else {
        pinMode(parser()->pin(), INPUT);
      }
    }
  }
};
#endif  // ARDUINO
