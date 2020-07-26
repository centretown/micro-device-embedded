// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#include "error_handler.h"  // NOLINT
#include "json_writer.h"    // NOLINT
class HttpFormatter : public ErrorHandler {
 public:
  explicit HttpFormatter(JsonWriter* writer) : ErrorHandler(writer) {}
  ~HttpFormatter() {}

  inline const char* ok() { return this->ok_; }
  inline const char* web() { return this->web_; }

  const String& Response() {
    if (this->ok()) {
      return this->ok_;
    }
  }

 private:
  const char* ok_ = R"~~(
HTTP/1.1 200 OK
Content-type:application/json
Access-Control-Allow-Origin: "*"
)~~";
  const char* web_ = R"~~(
HTTP/1.1 200 OK
Content-type:text/html

<html><body>Hello World!</body></html>
)~~";
};
