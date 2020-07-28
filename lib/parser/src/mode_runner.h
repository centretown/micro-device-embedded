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
#if defined(ARDUINO)
    if (args()->mode() == 'o') {
      pinMode(args()->pin(), OUTPUT);
    } else {
      pinMode(args()->pin(), INPUT);
    }
#else
    if (args()->mode() == 'o') {
      printf("pinMode(%d, OUTPUT);\n", args()->pin());
    } else {
      printf("pinMode(%d, INPUT);\n", args()->pin());
    }
#endif  // ARDUINO
  }
};
