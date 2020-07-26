// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#if defined(ARDUINO)
#include "process_parser.h"  // NOLINT
#include "process_runner.h"  // NOLINT

ProcessRunner* BuildProcessRunner(Process* process) {
  return new ProcessRunner(process);
}
#endif  // ARDUINO
