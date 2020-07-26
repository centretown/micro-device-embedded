// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include "mode.h"  // NOLINT

class Pin : public Mode {
 public:
  Pin() {}
  ~Pin() {}

  inline auto value() -> int { return this->value_; }
  inline auto set_value(int value) -> void { value_ = value; }

 private:
  int value_;
};
