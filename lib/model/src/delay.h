// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <stdint.h>

class Delay {
 public:
  Delay() {}
  ~Delay() {}

  inline uint32_t duration() { return this->duration_; }
  inline void set_duration(uint32_t duration) { duration_ = duration; }

 private:
  uint32_t duration_ = 0;
};
