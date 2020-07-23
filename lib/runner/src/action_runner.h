// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT
#if defined(ARDUINO)
#pragma once
#include "action_parser.h"  // NOLINT
#include "delay_runner.h"   // NOLINT
#include "mode_runner.h"    // NOLINT
#include "pin_runner.h"     // NOLINT
#include "runner.h"         // NOLINT

class ActionRunner : public Runner<ActionParser> {
 public:
  explicit ActionRunner(ActionParser* parser);
  ~ActionRunner() {}

  void Run() override;

 private:
  union {
    DelayRunner* d;
    ModeRunner* m;
    PinRunner* p;
  } runner_;
};
#endif  // ARDUINO
