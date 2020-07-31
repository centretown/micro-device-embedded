// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <operation.h>
#include <writer.h>

// create a runnable class derived from model T
template <class T>
class Runner : public Operation {
 public:
  explicit Runner(T* args, Writer* writer) : Operation(writer) {
    this->args_ = args;
  }
  virtual ~Runner() {}

  inline T* args() { return this->args_; }

 private:
  T* args_ = NULL;
};
