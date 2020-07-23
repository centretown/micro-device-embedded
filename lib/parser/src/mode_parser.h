// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once
#include <ArduinoJson.h>

#include "./parser.h"

class ModeParser : public Parser {
 public:
  ModeParser() {}
  ~ModeParser() {}

  void Parse(const JsonObject &doc) override;

  inline auto pin() -> uint8_t { return this->pin_; }
  inline auto set_pin(uint8_t pin) -> void { this->pin_ = pin; }

  inline auto signal() -> char { return this->signal_; }
  inline auto set_signal(String signal) -> void {
    this->signal_ = signal.charAt(0);
  }

  inline auto mode() -> char { return this->mode_; }
  inline auto set_mode(String mode) -> void { this->mode_ = mode.charAt(0); }

 private:
  uint8_t pin_;
  char mode_;
  char signal_;
};
