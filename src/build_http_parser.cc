// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "http_parser.h"  // NOLINT
#include "http_text.h"    // NOLINT
#include "writer.h"       // NOLINT

HttpParser* BuildHttpParser(char* httpRequest, Writer* writer,
                            HttpText* httpText) {
  HttpParser* parser = new HttpParser(writer, httpText);
  Text text(httpRequest);
  parser->Parse(text);
  return parser;
}
