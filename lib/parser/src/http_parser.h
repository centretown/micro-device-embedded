// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once
#include <ArduinoJson.h>

#include "http_text.h"  // NOLINT
#include "parser.h"     // NOLINT
#include "text.h"       // NOLINT
#include "writer.h"     // NOLINT

class HttpParser : public Parser<HttpText, Text> {
 public:
  explicit HttpParser(Writer* writer, HttpText* args) : Parser(writer, args) {}
  ~HttpParser() {}

  // extracts the path, version, method and body of an http request
  void Parse(const Text& text) override;
};
