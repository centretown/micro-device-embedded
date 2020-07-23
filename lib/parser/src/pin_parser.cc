// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "pin_parser.h"  //NOLINT

const int maxPins = 16;

void PinParser::Parse(const JsonObject& obj) {
  ModeParser::Parse(obj);
  if (this->ok() == false) return;

  int value = obj["value"];
  this->set_value(value);
  if (this->value() < 0 || this->value() > 1) {
    this->AppendError("Value must be 1 or 0");
  }
}
