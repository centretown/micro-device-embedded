// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <stdint.h>

class Mode {
 public:
  Mode() {}
  ~Mode() {}

  inline auto pin() -> uint8_t { return this->pin_; }
  inline auto set_pin(uint8_t pin) -> void { this->pin_ = pin; }

  inline auto signal() -> char { return this->signal_; }
  inline auto set_signal(const char signal) -> void { this->signal_ = signal; }

  inline auto mode() -> char { return this->mode_; }
  inline auto set_mode(const char mode) -> void { this->mode_ = mode; }

 private:
  uint8_t pin_ = 0;
  char mode_ = ' ';
  char signal_ = ' ';
};
