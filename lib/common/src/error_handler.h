// // Copyright 2020, Dave Marsh, Centretown
// // All rights reserved. see LICENSE.TXT

// #pragma once
// #include <ArduinoJson.h>

// #include "writer.h"  // NOLINT

// class ErrorHandler {
//  public:
//   explicit ErrorHandler(Writer* writer) { this->writer_ = writer; }
//   ~ErrorHandler() {}
//   inline bool ok() { return this->ok_; }
//   inline Writer* writer() { return this->writer_; }

//   void AppendError(const char* msg) {
//     ok_ = false;
//     writer_->WriteError(msg);
//   }
//   void AppendError(const char* prefix, const char* suffix) {
//     ok_ = false;
//     writer_->WriteError(prefix, suffix);
//   }
//   void AppendError(const char* msg, int num) {
//     ok_ = false;
//     writer_->WriteError(msg, num);
//   }

//   const char* err(char* buf, size_t len);

//  private:
//   bool ok_ = true;
//   Writer* writer_;
// };
