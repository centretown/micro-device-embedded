// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT
#pragma once

#include "op.h"       // NOLINT
#include "process.h"  // NOLINT
#include "runner.h"   // NOLINT

class ProcessRunner : public Runner<Process> {
 public:
  explicit ProcessRunner(Process* process, Writer* writer);
  ~ProcessRunner() {}

  void Run() override;
  void RunOps(Op** ops, size_t length);
};
