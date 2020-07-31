// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <process_runner.h>

ProcessRunner::ProcessRunner(Process* process, Writer* writer)
    : Runner(process, writer) {}

void ProcessRunner::Run() {
  auto process = this->args();
  if (process->is_setup_ == false) {
    process->is_setup_ = true;
    this->RunOps(process->setup(), process->setup_length());
  }
  this->RunOps(process->loop(), process->loop_length());
}

void ProcessRunner::RunOps(Operation** ops, size_t length) {
  for (auto i = 0; i < length; ++i) {
    ops[i]->Run();
  }
}

void ProcessRunner::set_writer(Writer* writer) {
  Operation::set_writer(writer);
  Process* process = this->args();
  Operation** setup = process->setup();
  for (auto i = 0; i < process->setup_length(); ++i) {
    setup[i]->set_writer(writer);
  }
  Operation** loop = process->loop();
  for (auto i = 0; i < process->loop_length(); ++i) {
    loop[i]->set_writer(writer);
  }
}
