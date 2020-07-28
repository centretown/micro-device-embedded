// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <my_strings.h>
#include <op.h>

class Process {
 public:
  Process() {}
  ~Process() {}

  inline char* label() { return this->label_; }
  inline void set_label(const char* label) {
    copyString(this->label_, label, sizeof(this->label_));
  }

  inline char* deviceKey() { return this->deviceKey_; }

  inline void set_deviceKey(const char* deviceKey) {
    copyString(this->deviceKey_, deviceKey, sizeof(this->deviceKey_));
  }

  inline char* purpose() { return this->purpose_; }
  inline void set_purpose(const char* purpose) {
    copyString(this->purpose_, purpose, sizeof(this->purpose_));
  }

  inline Op** setup() { return this->setup_; }
  inline void set_setup(Op** setup) { this->setup_ = setup; }
  inline size_t setup_length() { return this->setup_length_; }
  inline void set_setup_length(size_t length) { this->setup_length_ = length; }

  inline Op** loop() { return this->loop_; }
  inline void set_loop(Op** loop) { this->loop_ = loop; }
  inline size_t loop_length() { return this->loop_length_; }
  inline void set_loop_length(size_t length) { this->loop_length_ = length; }

  bool is_setup_ = false;

 private:
  char label_[32] = {0};
  char deviceKey_[32] = {0};
  char purpose_[128] = {0};
  Op** setup_ = NULL;
  size_t setup_length_ = 0;
  Op** loop_ = NULL;
  size_t loop_length_ = 0;
};
