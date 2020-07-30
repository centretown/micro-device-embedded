// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <stdio.h>
#endif  // ARDUINO

#include <hall.h>
#include <runner.h>

class HallRunner : public Runner<Hall> {
 public:
  explicit HallRunner(Hall* hall, Writer* writer) : Runner(hall, writer) {}
  ~HallRunner() {}
  void Run() override {
    auto hall = this->args();
#if defined(ARDUINO)
    int measurement = hallRead();
    hall->set_measurement(measurement);
#else
    // hall->set_measurement(measurement_);
    printf("hallRead() = %d;\n", hall->measurement());
#endif  // ARDUINO
  }
};
