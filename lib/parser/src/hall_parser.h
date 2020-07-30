// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <ArduinoJson.h>
#include <hall.h>
#include <json_object_parser.h>
#include <writer.h>
class HallParser : public JsonObjectParser<Hall> {
 public:
  explicit HallParser(Writer* writer, Hall* args)
      : JsonObjectParser(writer, args) {}
  ~HallParser() {}

  void Parse(const JsonObject& obj) override {
    this->args()->set_measurement(obj["measurement"]);
  }
};
