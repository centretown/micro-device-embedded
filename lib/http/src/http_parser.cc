// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "http_parser.h"  // NOLINT

static const String CONTENT_LENGTH = "Content-Length: ";

// Parses an http post request, verifies and stores
// the method, path, version and body of the request
void HttpParser::Parse(const String &source) {
  // ensure no overflows, be wary of a long path
  auto len = source.indexOf("\n");
  if (len < 0 || len > 128) {
    this->AppendError("Header's first line too long: ", len);
    return;
  }

  char method[8], path[104], version[16];
  sscanf(source.c_str(), "%s %s %s\n", method, path, version);
  this->set_method(method);
  this->set_path(path);
  this->set_version(version);

  if (this->method() != "POST") {
    this->AppendError("Method is not POST: " + this->method());
    return;
  }

  auto begin = source.indexOf(CONTENT_LENGTH);
  if (begin < 0) {
    this->AppendError(CONTENT_LENGTH + " missing");
    return;
  }

  auto end = source.indexOf("\n", begin);
  if (end < 0) {
    this->AppendError(CONTENT_LENGTH + " requires terminating line feed");
    return;
  }

  auto contentLength =
      source.substring(begin + CONTENT_LENGTH.length(), end).toInt();
  if (contentLength <= 0) {
    this->AppendError(CONTENT_LENGTH + " requires terminating line feed");
    return;
  }

  this->set_body(
      source.substring(source.length() - contentLength, source.length()));
}
