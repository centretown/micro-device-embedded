// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "process_parser.h"  // NOLINT

ProcessParser* BuildProcessParser(const char* body, Writer* writer) {
// ArduinoJson assistant calculates capacity = 924 (ESP32), when parsing test
// data of length = 686 (single space indentation with line feeds). Doubling
// the body length should provide an adequate margin for error on ESP32 but
// may fall short the on native platform "Sizes can be significantly larger on
// a computer."
#ifdef ARDUINO
  size_t multiplier = 2;
#else
  size_t multiplier = 3;
#endif
  // from the heap to be safe
  DynamicJsonDocument doc = DynamicJsonDocument(strlen(body) * multiplier);
  auto parser = new ProcessParser(writer);
  DeserializationError err = deserializeJson(doc, body);
  if (err) {
    char buf[80];
    snprintf(buf, sizeof(buf), "DeserializeJson error: %s", err.c_str());
    parser->WriteError(buf);
  } else {
    parser->Parse(doc.as<JsonObject>());
  }
  return parser;
}
