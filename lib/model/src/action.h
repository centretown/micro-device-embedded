// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <op.h>
#include <stdlib.h>

class Action {
 public:
  Action() {}
  // DO NOT DELETE op it is managed by processRunner
  ~Action() {}

  inline int sequence() { return this->sequence_; }
  inline void set_sequence(int sequence) { this->sequence_ = sequence; }

  inline char type() { return this->type_; }
  inline void set_type(char type) { this->type_ = type; }

  inline Op *op() { return this->op_; }
  inline void set_op(Op *op) { this->op_ = op; }

 private:
  int sequence_ = 0;
  char type_ = ' ';
  Op *op_ = NULL;
};
