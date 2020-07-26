// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once
#include <ArduinoJson.h>

#include "json_object_parser.h"  // NOLINT
#include "mode.h"                // NOLINT
#include "writer.h"              // NOLINT

class ModeParser : public JsonObjectParser<Mode> {
 public:
  explicit ModeParser(Writer* writer) : JsonObjectParser(writer) {}
  ~ModeParser() {}

  void Parse(const JsonObject& doc) override;
};
