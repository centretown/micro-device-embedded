// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <operation.h>
#include <process.h>
#include <runner.h>

class ProcessRunner : public Runner<Process> {
 public:
  explicit ProcessRunner(Process* process, Writer* writer);
  ~ProcessRunner() {}

  void Run() override;
  void RunOps(Operation** ops, size_t length);
};
