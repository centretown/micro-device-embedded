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
  args->set_setup(ParseOps(setup, args->setup_length()));

  auto loop = obj["loop"].as<JsonArray>();
  args->set_loop_length(loop.size());
  args->set_loop(ParseOps(loop, args->loop_length()));
}

Op** ProcessParser::ParseOps(const JsonArray& arr, size_t length) {
  Op** ops = NULL;
  if (length > 0) {
    Action action;
    ActionParser parser(this->writer(), &action);
    ops = new Op*[length];
    for (auto i = 0; i < length; ++i) {
      parser.clear();
      parser.Parse(arr[i].as<JsonObject>());
      if (!parser.ok()) {
        this->WriteError("Error parsing action: ", i);
      } else {
        ops[i] = parser.args()->op();
      }
    }
  }
  return ops;
}
