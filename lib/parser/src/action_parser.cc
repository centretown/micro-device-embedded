// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <action_parser.h>
#include <delay_parser.h>
#include <delay_runner.h>
#include <hall_parser.h>
#include <hall_runner.h>
#include <mode_parser.h>
#include <mode_runner.h>
#include <pin_parser.h>
#include <pin_runner.h>
#include <string.h>

void ActionParser::Parse(const JsonObject& obj) {
  auto args = this->args();
  auto writer = this->writer();
  args->set_sequence(obj["sequence"]);
  const char* type = obj["type"];
  if (strlen(type) == 0) {
    writer->Write("Type is required");
    return;
  }

  JsonObject command = obj["command"];
  args->set_type(*type);
  switch (args->type()) {
    case 'M':  // MODE
    {
      ModeParser parser(this->writer(), new Mode());
      parser.Parse(command);
      if (parser.ok()) {
        auto modeArgs = parser.args();
        auto runner = new ModeRunner(modeArgs, writer);
        args->set_op(runner);
      } else {
        writer->Write("Error parsing Mode", args->sequence());
      }
    } break;
    case 'D':  // DELAY
    {
      DelayParser parser(this->writer(), new Delay());
      parser.Parse(command);
      if (parser.ok()) {
        auto delayArgs = parser.args();
        auto runner = new DelayRunner(delayArgs, writer);
        args->set_op(runner);
      } else {
        writer->Write("Error parsing Delay", args->sequence());
      }
    } break;
    case 'P':  // PIN I/O
    {
      PinParser parser(this->writer(), new Pin());
      parser.Parse(command);
      if (parser.ok()) {
        auto pinArgs = parser.args();
        auto runner = new PinRunner(pinArgs, writer);
        args->set_op(runner);
      } else {
        writer->Write("Error parsing Pin", args->sequence());
      }
    } break;
    case 'H':  // HALL READER
    {
      HallParser parser(this->writer(), new Hall());
      parser.Parse(command);
      if (parser.ok()) {
        auto hallArgs = parser.args();
        auto runner = new HallRunner(hallArgs, writer);
        args->set_op(runner);
      } else {
        writer->Write("Error parsing Hall", args->sequence());
      }
    } break;
    default:
      writer->Write("Type is unrecognized");
      return;
  }
}
