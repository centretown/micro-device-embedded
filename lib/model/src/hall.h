// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

class Hall {
 public:
  Hall() {}
  ~Hall() {}

  inline int measurement() { return this->measurement_; }
  inline void set_measurement(int measurement) {
    this->measurement_ = measurement;
  }

 private:
  int measurement_ = 0;
};
