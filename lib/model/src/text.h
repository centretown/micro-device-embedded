// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

// #include <stddef.h>

class Text {
 public:
  explicit Text(char* buffer) { this->buffer_ = buffer; }
  ~Text() {}

  inline char* buffer() { return this->buffer_; }
  inline void set_buffer(char* buffer) { this->buffer_ = buffer; }

  //  private:
  char* buffer_ = NULL;
};
