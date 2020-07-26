// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#include "http_parser.h"     // NOLINT
#include "process_parser.h"  // NOLINT
#include "process_runner.h"  // NOLINT

HttpParser* BuildHttpParser(char* httpRequest, Writer* writer);
ProcessParser* BuildProcessParser(const char* body, Writer* writer);
ProcessRunner* BuildProcessRunner(Process* process);
