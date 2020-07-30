// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <my_strings.h>
class Writer {
 public:
  Writer() {
    this->set_array_name("results");
    this->set_key_name("result");
  }
  Writer(const char *array_name, const char *key_name) {
    this->set_array_name(array_name);
    this->set_key_name(key_name);
  }
  virtual ~Writer() {}

  inline const char *array_name() { return this->array_name_; }
  inline const void set_array_name(const char *name) {
    copyString(this->array_name_, name, sizeof(this->array_name_));
  }

  inline const char *key_name() { return this->key_name_; }
  inline const void set_key_name(const char *name) {
    copyString(this->key_name_, name, sizeof(this->key_name_));
  }

  virtual void Write(const char *value) = 0;
  virtual void Write(int value) = 0;
  virtual void Write(const char *message, int value) = 0;
  virtual void Write(const char *message, const char *value) = 0;
  virtual char *Read(char *output, size_t length) = 0;
  virtual size_t Length() = 0;

 private:
  char array_name_[32] = {0};
  char key_name_[32] = {0};
};
