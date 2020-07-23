// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#include "http_parser.h"     // NOLINT
#include "process_parser.h"  // NOLINT
#include "process_runner.h"  // NOLINT

HttpParser* BuildHttpParser(const String& httpRequest);
ProcessParser* BuildProcessParser(const String& body);
ProcessRunner* BuildProcessRunner(ProcessParser* parser);
