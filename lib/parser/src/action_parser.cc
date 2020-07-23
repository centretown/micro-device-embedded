// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "action_parser.h"  // NOLINT

#include "delay_parser.h"  // NOLINT
#include "mode_parser.h"   // NOLINT
#include "pin_parser.h"    // NOLINT

ActionParser* ActionParser::NoAction() {
  ActionParser* action = new ActionParser();
  action->set_sequence(0);
  action->set_type("delay");
  DelayParser* parser = new DelayParser();
  parser->set_duration(0);
  action->set_parser(parser);
  return action;
}

void ActionParser::Parse(const JsonObject& obj) {
  this->set_sequence(obj["sequence"]);
  String type = (const char*)obj["type"];
  if (type.length() == 0) {
    this->AppendError("Type is required");
    return;
  }

  set_type(type);
  Parser* parser = NULL;
  switch (this->type()) {
    case 'm':  // MODE
      parser = new ModeParser();
      break;
    case 'd':  // DELAY
      parser = new DelayParser();
      break;
    case 'p':  // PIN I/O
      parser = new PinParser();
      break;
    default:
      this->AppendError("Type is unrecognized");
      return;
  }

  parser->Parse(obj["command"]);
  if (!parser->ok()) {
    this->AppendError(parser->err());
    return;
  }

  set_parser(parser);
}
