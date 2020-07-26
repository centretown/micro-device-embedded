// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <stdlib.h>

#include "delay.h"  // NOLINT
#include "mode.h"   // NOLINT
#include "pin.h"    // NOLINT

#pragma once

class Op {
 public:
  Op() {}
  virtual ~Op() {}
  virtual void Run() = 0;
};
