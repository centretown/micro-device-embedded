// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once
#include <ArduinoJson.h>

class ErrorHandler {
 public:
  ErrorHandler() {}
  ~ErrorHandler() {}

  void AppendError(const String msg);
  void AppendError(const String msg, int num);

  inline String& err() { return this->err_; }
  inline bool ok() { return this->ok_; }

 private:
  String err_;
  bool ok_ = true;
};
