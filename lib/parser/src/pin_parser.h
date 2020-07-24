// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once
#include <ArduinoJson.h>

#include "mode_parser.h"  // NOLINT

class PinParser : public ModeParser {
 public:
  PinParser() : ModeParser() {}
  ~PinParser() {}

  void Parse(const JsonObject &obj) override;

  inline auto value() -> int { return this->value_; }
  inline auto set_value(int value) -> void { value_ = value; }

 private:
  int value_;
};
