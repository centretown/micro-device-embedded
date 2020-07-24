// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "error_handler.h"  // NOLINT

JsonWriter* ErrorHandler::writer_ = new JsonWriter(256);

void ErrorHandler::err(char* buf, size_t len) {
  this->writer_->ReadAll(buf, len);
}