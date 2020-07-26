// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "http_parser.h"  // NOLINT
#include "writer.h"

HttpParser* BuildHttpParser(char* httpRequest, Writer* writer) {
  HttpParser* parser = new HttpParser(writer);
  Text text(httpRequest);
  parser->Parse(text);
  return parser;
}
