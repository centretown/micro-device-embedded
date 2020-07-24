// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once
#include <ArduinoJson.h>

#include "json_writer.h"  // NOLINT

class ErrorHandler {
 public:
  static JsonWriter* writer_;

  ErrorHandler() {}
  ~ErrorHandler() {}
  inline bool ok() { return this->ok_; }

  void AppendError(const char* msg) {
    ok_ = false;
    writer_->WriteError(msg);
  }
  void AppendError(const char* prefix, const char* suffix) {
    ok_ = false;
    writer_->WriteError(prefix, suffix);
  }
  void AppendError(const char* msg, int num) {
    ok_ = false;
    writer_->WriteError(msg, num);
  }
  void err(char* buf, size_t len);

 private:
  bool ok_ = true;
};
