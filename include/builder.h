// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#include "http_parser.h"     // NOLINT
#include "process_parser.h"  // NOLINT
#include "process_runner.h"  // NOLINT

HttpParser* BuildHttpParser(char* httpRequest);
ProcessParser* BuildProcessParser(const char* body);
ProcessRunner* BuildProcessRunner(ProcessParser* parser);
