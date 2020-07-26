// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include "action.h"              // NOLINT
#include "json_object_parser.h"  // NOLINT
#include "parser.h"              // NOLINT
#include "writer.h"              // NOLINT

class ActionParser : public JsonObjectParser<Action> {
 public:
  explicit ActionParser(Writer* writer) : JsonObjectParser<Action>(writer) {}
  ~ActionParser() {}

  // command overrides
  void Parse(const JsonObject& obj) override;
};
