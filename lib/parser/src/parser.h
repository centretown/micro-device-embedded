// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <ArduinoJson.h>
#include <writer.h>

// parse class "O" to derive class "T"
template <class T, class O>
class Parser {
 public:
  explicit Parser(Writer *writer, T *args) {
    this->args_ = args;
    this->writer_ = writer;
  }
  virtual ~Parser() {}

  // parse and validatehello world again
  virtual void Parse(const O &o) = 0;

  inline Writer *writer() { return this->writer_; }
  inline bool ok() { return this->ok_; }
  inline void clear() { this->ok_ = true; }

  inline T *args() { return args_; }
  inline void set_args(T *args) { args_ = args; }

  void WriteData(const char *message) {
    this->ok_ = false;
    this->writer_->WriteData(message);
  }
  void WriteError(const char *message) {
    this->ok_ = false;
    this->writer_->WriteError(message);
  }
  void WriteError(const char *message, const int num) {
    this->ok_ = false;
    this->writer_->WriteError(message, num);
  }
  void WriteError(const char *suffix, const char *prefix) {
    this->ok_ = false;
    this->writer_->WriteError(suffix, prefix);
  }
  char *ReadData(char *output, size_t outputSize) {
    return this->writer_->ReadData(output, outputSize);
  }
  char *ReadError(char *output, size_t outputSize) {
    return this->writer_->ReadError(output, outputSize);
  }

 private:
  Writer *writer_ = NULL;
  bool ok_ = true;
  T *args_ = NULL;
};
