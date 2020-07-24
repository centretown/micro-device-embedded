// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#include <ArduinoJson.h>

#include "parser.h"  // NOLINT

class DelayParser : public Parser {
 public:
  DelayParser() : Parser() {}
  ~DelayParser() {}

  // void Exec() override;
  void Parse(const JsonObject& obj) override;

  inline auto duration() -> uint32_t { return this->duration_; }
  inline auto set_duration(uint32_t duration) -> void { duration_ = duration; }

 private:
  uint32_t duration_ = 0;
};
