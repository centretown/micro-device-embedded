// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once
#include <ArduinoJson.h>

#include "mode_parser.h"  // NOLINT
#include "pin.h"          // NOLINT
#include "writer.h"       // NOLINT

class PinParser : public JsonObjectParser<Pin> {
 public:
  explicit PinParser(Writer* writer) : JsonObjectParser(writer) {
    mode_parser_ = new ModeParser(writer);
  }
  ~PinParser() { delete mode_parser_; }

  void Parse(const JsonObject& obj) override;

  inline int value() { return this->value_; }
  inline void set_value(int value) { value_ = value; }

 private:
  int value_ = 0;
  ModeParser* mode_parser_ = NULL;
};
