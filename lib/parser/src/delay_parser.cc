// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "delay_parser.h"  // NOLINT

void DelayParser::Parse(const JsonObject &obj) {
  if (!obj["duration"]) {
    this->AppendError("Duration missing");
    return;
  }
  this->set_duration(obj["duration"]);
}
