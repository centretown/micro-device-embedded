// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <stdio.h>
#endif  // ARDUINO

#include "mode.h"         // NOLINT
#include "mode_parser.h"  // NOLINT
#include "runner.h"       // NOLINT

class ModeRunner : public Runner<Mode> {
 public:
  explicit ModeRunner(Mode* mode) : Runner<Mode>(mode) {}
  ~ModeRunner() {}

  void Run() override {
    auto mode = this->args();
#if defined(ARDUINO)
    if (mode->mode() == 'o') {
      pinMode(mode->pin(), OUTPUT);
    } else {
      pinMode(mode->pin(), INPUT);
    }
#else
    if (mode->mode() == 'o') {
      printf("pinMode(%d, OUTPUT);\n", mode->pin());
    } else {
      printf("pinMode(%d, INPUT);\n", mode->pin());
    }
#endif  // ARDUINO
  }
};
