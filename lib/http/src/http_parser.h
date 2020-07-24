// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once
#include <ArduinoJson.h>

#include "error_handler.h"  // NOLINT

class HttpParser : public ErrorHandler {
 public:
  HttpParser() {}
  ~HttpParser() {}

  inline const char* path() { return this->path_; }
  inline const char* version() { return this->version_; }
  inline const char* method() { return this->method_; }
  inline char* body() { return this->body_; }

  // extracts the path, version, method and body of an http request
  void Parse(char* source);

 private:
  char path_[100], version_[16], method_[8], *body_;
};
