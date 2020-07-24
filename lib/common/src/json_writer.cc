// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "json_writer.h"  // NOLINT

JsonWriter::JsonWriter(size_t size) : Writer() {
  this->doc_ = new DynamicJsonDocument(size);
}

JsonWriter::~JsonWriter() { delete this->doc_; }

void JsonWriter::Write(const char *message) {
  if (this->data_.isNull()) {
    this->data_ = this->doc_->createNestedArray("data");
  }
  auto obj = this->data_.createNestedObject();
  obj["message"] = message;
}

void JsonWriter::WriteError(const char *message) {
  if (this->errors_.isNull()) {
    this->errors_ = this->doc_->createNestedArray("errors");
  }
  auto obj = this->errors_.createNestedObject();
  obj["message"] = message;
}

void JsonWriter::WriteError(const char *message, int num) {
  char buf[80];
  snprintf(buf, sizeof(buf), "%s %d", message, num);
  this->WriteError(buf);
}

void JsonWriter::WriteError(const char *prefix, const char *suffix) {
  char buf[160];
  snprintf(buf, sizeof(buf), "%s %s", prefix, suffix);
  this->WriteError(buf);
}

void JsonWriter::ReadAll(char *output, size_t outputSize) {
  serializeJson(*this->doc_, output, outputSize);
}
