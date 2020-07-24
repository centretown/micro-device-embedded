// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "http_parser.h"  // NOLINT

HttpParser* BuildHttpParser(char* httpRequest) {
  HttpParser* parser = new HttpParser();
  parser->Parse(httpRequest);
  return parser;
}
