// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <action.h>
#include <delay_parser.h>
#include <delay_runner.h>
#include <hall_parser.h>
#include <hall_runner.h>
#include <json_object_parser.h>
#include <mode_parser.h>
#include <mode_runner.h>
#include <parser.h>
#include <pin_parser.h>
#include <pin_runner.h>
#include <writer.h>

class ActionParser : public JsonObjectParser<Action> {
 public:
  explicit ActionParser(Writer* writer, Action* args)
      : JsonObjectParser<Action>(writer, args) {}
  ~ActionParser() {}

  void Parse(const JsonObject& obj) override;
};
