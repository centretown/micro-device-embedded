// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <ArduinoJson.h>
#include <writer.h>

// derive class "T" by parsing class "O"
template <class T, class O>
class Parser {
 public:
  explicit Parser(Writer *writer, T *args) {
    this->args_ = args;
    this->writer_ = writer;
    this->initial_length_ = writer->Length();
  }
  virtual ~Parser() {}

  virtual void Parse(const O &o) = 0;

  inline Writer *writer() { return this->writer_; }
  inline bool ok() { return this->writer_->Length() == this->initial_length_; }
  inline void set_ok() { this->initial_length_ = this->writer_->Length(); }

  inline T *args() { return args_; }
  inline void set_args(T *args) { args_ = args; }

 private:
  Writer *writer_ = NULL;
  T *args_ = NULL;
  size_t initial_length_ = 0;
};
