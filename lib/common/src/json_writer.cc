// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include <json_writer.h>
#include <my_strings.h>

JsonWriter::JsonWriter(size_t size) : Writer() {
  this->doc_ = new DynamicJsonDocument(size);
  this->obj_ = this->doc_->createNestedObject();
}

JsonWriter::~JsonWriter() { delete this->doc_; }

void JsonWriter::WriteData(const char *message) {
  if (this->data_.isNull()) {
    this->data_ = this->obj_.createNestedArray("data");
  }
  auto obj = this->data_.createNestedObject();
  obj["message"] = message;
}

void JsonWriter::WriteError(const char *message) {
  if (this->errors_.isNull()) {
    this->errors_ = this->obj_.createNestedArray("errors");
  }
  auto obj = this->errors_.createNestedObject();
  obj["message"] = message;
}

void JsonWriter::WriteError(const char *message, int num) {
  char buf[160];
  snprintf(buf, sizeof(buf), "%s %d", message, num);
  this->WriteError(buf);
}

void JsonWriter::WriteError(const char *prefix, const char *suffix) {
  char buf[256];
  snprintf(buf, sizeof(buf), "%s %s", prefix, suffix);
  this->WriteError(buf);
}

char *JsonWriter::ReadData(char *output, size_t outputSize) {
  if (this->data_.isNull())
    copyString(output, "no data", outputSize);
  else
    serializeJson(this->data_, output, outputSize);
  return output;
}

char *JsonWriter::ReadError(char *output, size_t outputSize) {
  if (this->errors_.isNull())
    copyString(output, "no data", outputSize);
  else
    serializeJson(this->errors_, output, outputSize);
  return output;
}
