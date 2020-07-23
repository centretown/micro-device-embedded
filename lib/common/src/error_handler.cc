// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "error_handler.h"  // NOLINT

#include <WString.h>

// error handling
void ErrorHandler::AppendError(const String msg) {
  this->ok_ = false;
  this->err_.concat(msg);
  this->err_.concat('\n');
}

void ErrorHandler::AppendError(const String msg, int num) {
  String buf(num);
  this->ok_ = false;
  this->err_.concat(msg);
  this->err_.concat(buf);
  this->err_.concat('\n');
}
