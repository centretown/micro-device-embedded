// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <writer.h>

class Operation {
 public:
  explicit Operation(Writer* writer) {}
  virtual ~Operation() {}
  virtual void Run() = 0;
  inline Writer* writer() { return this->writer_; }
  virtual inline void set_writer(Writer* writer) { this->writer_ = writer; }

 private:
  Writer* writer_ = NULL;
};
