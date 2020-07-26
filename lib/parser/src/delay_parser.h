// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <ArduinoJson.h>

#include "delay.h"               // NOLINT
#include "json_object_parser.h"  // NOLINT
#include "writer.h"              // NOLINT

class DelayParser : public JsonObjectParser<Delay> {
 public:
  explicit DelayParser(Writer* writer) : JsonObjectParser(writer) {}
  ~DelayParser() {}

  void Parse(const JsonObject& obj) override;
};
