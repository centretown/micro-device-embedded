// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "action_parser.h"  // NOLINT

#include "delay_parser.h"  // NOLINT
#include "mode_parser.h"   // NOLINT
#include "pin_parser.h"    // NOLINT

void ActionParser::Parse(const JsonObject& obj) {
  this->set_sequence(obj["sequence"]);
  const char* type = obj["type"];
  if (strlen(type) == 0) {
    this->AppendError("Type is required");
    return;
  }

  set_type(*type);
  Parser* parser = NULL;
  switch (this->type()) {
    case 'M':  // MODE
      parser = new ModeParser();
      break;
    case 'D':  // DELAY
      parser = new DelayParser();
      break;
    case 'P':  // PIN I/O
      parser = new PinParser();
      break;
    default:
      this->AppendError("Type is unrecognized");
      return;
  }

  parser->Parse(obj["command"]);
  if (!parser->ok()) {
    this->AppendError("Command error");
    return;
  }

  set_parser(parser);
}
