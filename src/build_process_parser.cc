// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "process_parser.h"  // NOLINT

static const size_t kBufferSize = 160;

ProcessParser* BuildProcessParser(const char* body, Writer* writer,
                                  Process* process) {
#ifdef ARDUINO
  size_t multiplier = 2;  // 32 bit environment
#else                     // NATIVE
  size_t multiplier = 3;  // 64 bit environment
#endif
  // "Dynamic" stores on heap
  DynamicJsonDocument doc = DynamicJsonDocument(strlen(body) * multiplier);
  auto parser = new ProcessParser(writer, process);
  DeserializationError err = deserializeJson(doc, body);
  if (err) {
    char buf[kBufferSize];
    snprintf(buf, sizeof(buf), "DeserializeJson error: %s", err.c_str());
    parser->WriteError(buf);
  } else {
    parser->Parse(doc.as<JsonObject>());
  }
  return parser;
}
