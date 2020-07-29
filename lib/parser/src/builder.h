// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once
#include <http_parser.h>
#include <http_text.h>
#include <process_parser.h>

HttpParser* BuildHttpParser(char* httpRequest, Writer* writer,
                            HttpText* httpText);
ProcessParser* BuildProcessParser(const char* body, Writer* writer,
                                  Process* process);
