// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "process_runner.h"  // NOLINT

#include "process_parser.h"  // NOLINT

ProcessRunner::ProcessRunner(Process* process) : Runner(process) {}

void ProcessRunner::Run() {
  auto args = this->args();
  if (args->is_setup_ == false) {
    // ensure this runs once
    args->is_setup_ = true;
    this->RunOps(args->setup(), args->setup_length());
  }
  this->RunOps(args->loop(), args->loop_length());
}

void ProcessRunner::RunOps(Op** ops, size_t length) {
  for (auto i = 0; i < length; ++i) {
    ops[i]->Run();
  }
}
