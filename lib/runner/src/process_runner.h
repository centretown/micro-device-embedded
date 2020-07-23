// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT
#if defined(ARDUINO)
#pragma once

#include "action_runner.h"   // NOLINT
#include "process_parser.h"  // NOLINT
#include "runner.h"          // NOLINT

class ProcessRunner : public Runner<ProcessParser> {
 public:
  explicit ProcessRunner(ProcessParser* parser);
  ~ProcessRunner() {
    delete[] this->setup_actions_;
    delete[] this->loop_actions_;
  }

  void Run() override;
  void RunActions(ActionRunner** actions, size_t length);

  inline bool setup() { return setup_; }
  inline void set_setup() { setup_ = true; }

  inline size_t setup_length() { return this->setup_length_; }
  inline void set_setup_length(size_t length) { this->loop_length_ = length; }
  inline ActionRunner** setup_actions() { return this->setup_actions_; }
  inline void set_setup_actions(ActionRunner** actions) {
    this->setup_actions_ = actions;
  }

  inline size_t loop_length() { return this->setup_length_; }
  inline void set_loop_length(size_t length) { this->loop_length_ = length; }
  inline ActionRunner** loop_actions() { return this->loop_actions_; }
  inline void set_loop_actions(ActionRunner** actions) {
    this->loop_actions_ = actions;
  }

 private:
  bool setup_ = false;
  ActionRunner** setup_actions_ = NULL;
  size_t setup_length_ = 0;
  ActionRunner** loop_actions_ = NULL;
  size_t loop_length_ = 0;
};
#endif  // ARDUINO
