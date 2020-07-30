// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "pin_parser.h"  // NOLINT

void PinParser::Parse(const JsonObject& obj) {
  this->mode_parser_->Parse(obj);
  if (this->ok() == false) return;

  int value = obj["value"];
  auto args = this->args();
  args->set_value(value);
  if (args->value() < 0 || args->value() > 1) {
    this->writer()->Write("Value must be 1 or 0");
  }
}
