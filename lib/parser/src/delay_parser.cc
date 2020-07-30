// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "delay_parser.h"  // NOLINT

void DelayParser::Parse(const JsonObject& obj) {
  if (!obj["duration"]) {
    this->writer()->Write("Duration missing");
    return;
  }
  this->args()->set_duration(obj["duration"]);
}
