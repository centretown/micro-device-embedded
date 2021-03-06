// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <stdio.h>
#endif  // ARDUINO

#include <delay.h>
#include <runner.h>

class DelayRunner : public Runner<Delay> {
 public:
  explicit DelayRunner(Delay* args, Writer* writer) : Runner(args, writer) {}
  ~DelayRunner() {}

  void Run() override {
#if defined(ARDUINO)
    delay(args()->duration());
#else
    printf("delay(%d);\n", args()->duration());
#endif  // ARDUINO
  }
};
