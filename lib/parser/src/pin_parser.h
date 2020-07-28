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
  explicit PinParser(Writer* writer, Pin* args)
      : JsonObjectParser(writer, args) {
    mode_parser_ = new ModeParser(writer, args);
  }
  ~PinParser() { delete mode_parser_; }

  void Parse(const JsonObject& obj) override;

 private:
  ModeParser* mode_parser_ = NULL;
};
