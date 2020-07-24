// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT
#pragma once

#include <ArduinoJson.h>

#include "error_handler.h"  // NOLINT

class Parser : public ErrorHandler {
 public:
  Parser() : ErrorHandler() {}
  virtual ~Parser() {}
  // parse and validate
  virtual void Parse(const JsonObject& obj) = 0;
};
