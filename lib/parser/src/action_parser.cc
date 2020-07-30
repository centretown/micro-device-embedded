// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <action_parser.h>

template <class Model, class Parser, class Runner>
Operation* createOperation(Writer* writer, const JsonObject& command,
                           int sequence) {
  Parser parser(writer, new Model());
  parser.Parse(command);
  if (parser.ok()) {
    return new Runner(parser.args(), writer);
  }
  writer->Write("Error parsing action:", sequence);
  return NULL;
}

void ActionParser::Parse(const JsonObject& obj) {
  Action* action = this->args();
  auto writer = this->writer();
  if (obj["sequence"].isNull()) {
    writer->Write("Sequence number required");
    return;
  }
  action->set_sequence(obj["sequence"]);
  const char* type = obj["type"];
  if (strlen(type) == 0) {
    writer->Write("Action Type required");
    return;
  }

  JsonObject command = obj["command"];
  action->set_type(*type);
  switch (action->type()) {
    case 'M':
      action->set_operation(createOperation<Mode, ModeParser, ModeRunner>(
          writer, command, action->sequence()));
      break;
    case 'D':
      action->set_operation(createOperation<Delay, DelayParser, DelayRunner>(
          writer, command, action->sequence()));
      break;
    case 'P':
      action->set_operation(createOperation<Pin, PinParser, PinRunner>(
          writer, command, action->sequence()));
      break;
    case 'H':
      action->set_operation(createOperation<Hall, HallParser, HallRunner>(
          writer, command, action->sequence()));
      break;
    default:
      writer->Write("Unrecognized type:", action->type());
      return;
  }
}
