// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include <action_parser.h>
#include <process_parser.h>

void ProcessParser::Parse(const JsonObject& obj) {
  auto args = this->args();
  // no edit necessary right now
  args->set_label(obj["label"]);
  args->set_deviceKey(obj["deviceKey"]);
  args->set_purpose(obj["purpose"]);

  // edit these
  auto setup = obj["setup"].as<JsonArray>();
  args->set_setup_length(setup.size());
  args->set_setup(ParseOperations(setup, args->setup_length()));

  auto loop = obj["loop"].as<JsonArray>();
  args->set_loop_length(loop.size());
  args->set_loop(ParseOperations(loop, args->loop_length()));
}

Operation** ProcessParser::ParseOperations(const JsonArray& arr,
                                           size_t length) {
  Operation** operations = NULL;
  if (length > 0) {
    operations = new Operation*[length];
    // use single action and parser for all operations
    Action action;
    ActionParser parser(this->writer(), &action);
    for (auto i = 0; i < length; ++i) {
      parser.set_ok();
      parser.Parse(arr[i].as<JsonObject>());
      if (!parser.ok()) {
        this->writer()->Write("Error parsing action:", i);
      } else {
        operations[i] = action.operation();
      }
    }
  }
  return operations;
}
