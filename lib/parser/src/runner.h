// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <op.h>
#include <writer.h>

// create a runnable class derived from model T
template <class T>
class Runner : public Op {
 public:
  explicit Runner(T* args, Writer* writer) {
    this->args_ = args;
    this->writer_ = writer;
  }
  virtual ~Runner() {}

  inline T* args() { return this->args_; }
  inline Writer* writer() { return this->writer_; }

 private:
  T* args_ = NULL;
  Writer* writer_ = NULL;
};
