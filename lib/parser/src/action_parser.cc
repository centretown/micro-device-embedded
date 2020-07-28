// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "action_parser.h"  // NOLINT

#include "delay_parser.h"  // NOLINT
#include "delay_runner.h"  // NOLINT
#include "mode_parser.h"   // NOLINT
#include "mode_runner.h"   // NOLINT
#include "pin_parser.h"    // NOLINT
#include "pin_runner.h"    // NOLINT

void ActionParser::Parse(const JsonObject& obj) {
  auto args = this->args();
  args->set_sequence(obj["sequence"]);
  const char* type = obj["type"];
  if (strlen(type) == 0) {
    this->WriteError("Type is required");
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
        auto runner = new ModeRunner(modeArgs);
        args->set_op(runner);
      } else {
        this->WriteError("Error parsing Mode ", args->sequence());
      }
    } break;
    case 'D':  // DELAY
    {
      DelayParser parser(this->writer(), new Delay());
      parser.Parse(command);
      if (parser.ok()) {
        auto delayArgs = parser.args();
        auto runner = new DelayRunner(delayArgs);
        args->set_op(runner);
      } else {
        this->WriteError("Error parsing Delay ", args->sequence());
      }
    } break;
    case 'P':  // PIN I/O
    {
      PinParser parser(this->writer(), new Pin());
      parser.Parse(command);
      if (parser.ok()) {
        auto pinArgs = parser.args();
        auto runner = new PinRunner(pinArgs);
        args->set_op(runner);
      } else {
        this->WriteError("Error parsing Pin ", args->sequence());
      }
    } break;
    default:
      this->WriteError("Type is unrecognized");
      return;
  }
}
