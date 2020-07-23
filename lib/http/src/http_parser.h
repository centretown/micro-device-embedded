// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once
#include <ArduinoJson.h>

#include "error_handler.h"  // NOLINT

class HttpParser : public ErrorHandler {
 public:
  HttpParser() {}
  ~HttpParser() {}

  inline const String& path() { return this->path_; }
  inline void set_path(const String& path) { this->path_ = path; }

  inline const String& version() { return this->version_; }
  inline void set_version(const String& version) { this->version_ = version; }

  inline const String& method() { return this->method_; }
  inline void set_method(String method) { this->method_ = method; }

  inline const String& body() { return this->body_; }
  inline void set_body(String body) { this->body_ = body; }

  // extracts the path, version, method and body of an http request
  void Parse(const String& source);

 private:
  String path_, version_, method_, body_;
};
