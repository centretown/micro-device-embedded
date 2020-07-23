// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "process_parser.h"  // NOLINT

#include "delay_parser.h"  // NOLINT

void ProcessParser::Parse(const JsonObject& obj) {
  // no edit necessary right now
  this->set_label(obj["label"]);
  this->set_deviceKey(obj["deviceKey"]);
  this->set_purpose(obj["purpose"]);

  // edit these
  auto arr = obj["setup"].as<JsonArray>();
  this->set_setup_length(arr.size());
  this->set_setup(ParseActions(arr, this->setup_length()));

  arr = obj["loop"].as<JsonArray>();
  this->set_loop_length(arr.size());
  this->set_loop(ParseActions(arr, this->loop_length()));
}

ActionParser** ProcessParser::ParseActions(const JsonArray& arr,
                                           size_t length) {
  ActionParser** actions = NULL;
  if (length > 0) {
    actions = new ActionParser*[length];
    for (auto i = 0; i < length; ++i) {
      ActionParser* action = new ActionParser();
      action->Parse(arr[i].as<JsonObject>());
      if (!action->ok()) {
        this->AppendError("Error parsing action: ", i);
      }
      actions[i] = action;
    }
  }
  return actions;
}
