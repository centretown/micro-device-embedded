// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once
#include <ArduinoJson.h>

#include "action_parser.h"       // NOLINT
#include "json_object_parser.h"  // NOLINT
#include "process.h"             // NOLINT
#include "writer.h"              // NOLINT

class ProcessParser : public JsonObjectParser<Process> {
 public:
  explicit ProcessParser(Writer* writer) : JsonObjectParser(writer) {}
  ~ProcessParser() {}

  void Parse(const JsonObject& obj) override;
  Op** ParseOps(const JsonArray& arr, size_t len);
};
