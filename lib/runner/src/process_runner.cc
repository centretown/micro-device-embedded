// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#if defined(ARDUINO)
#include "process_runner.h"  // NOLINT

#include "process_parser.h"  // NOLINT

ProcessRunner::ProcessRunner(ProcessParser* p) : Runner(p) {
  const auto parser = this->parser();
  if (parser->ok()) {
    this->set_setup_length(parser->setup_length());
    auto actions = new ActionRunner*[this->setup_length()];
    auto parsers = parser->setup();
    for (auto i = 0; this->setup_length(); ++i) {
      actions[i] = new ActionRunner(parsers[i]);
    }
    this->set_setup_actions(actions);

    this->set_loop_length(parser->loop_length());
    actions = new ActionRunner*[this->loop_length()];
    parsers = parser->loop();
    for (auto i = 0; this->loop_length(); ++i) {
      actions[i] = new ActionRunner(parsers[i]);
    }
    this->set_loop_actions(actions);
  }
}

void ProcessRunner::Run() {
  if (this->setup() == false) {
    // ensure this runs once
    this->set_setup();
    this->RunActions(this->setup_actions(), this->setup_length());
  }
  this->RunActions(this->loop_actions(), this->loop_length());
}

void ProcessRunner::RunActions(ActionRunner** actions, size_t length) {
  for (auto i = 0; i < length; ++i) {
    actions[i]->Run();
  }
}
#endif  // ARDUINO
