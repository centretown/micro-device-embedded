// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <operation.h>
#include <stdlib.h>

class Action {
 public:
  Action() {}
  ~Action() {}

  inline int sequence() { return this->sequence_; }
  inline void set_sequence(int sequence) { this->sequence_ = sequence; }

  inline char type() { return this->type_; }
  inline void set_type(char type) { this->type_ = type; }

  inline Operation *operation() { return this->operation_; }
  inline void set_operation(Operation *operation) {
    this->operation_ = operation;
  }

 private:
  int sequence_ = 0;
  char type_ = ' ';
  Operation *operation_ = NULL;
};
