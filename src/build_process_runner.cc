// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#if defined(ARDUINO)
#include "process_parser.h"  // NOLINT
#include "process_runner.h"  // NOLINT

ProcessRunner* BuildProcessRunner(ProcessParser* parser) {
  return new ProcessRunner(parser);
}
#endif  // ARDUINO
