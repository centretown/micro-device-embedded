// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#include <op.h>  // NOLINT

// create a runnable class derived from model T
template <class T>
class Runner : public Op {
 public:
  explicit Runner(T* args) { this->args_ = args; }
  virtual ~Runner() {}

  inline T* args() { return this->args_; }

 private:
  T* args_ = NULL;
};
