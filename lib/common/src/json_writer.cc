// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <json_writer.h>
#include <my_strings.h>

JsonWriter::JsonWriter(size_t size, const char *array_name,
                       const char *key_name)
    : Writer(array_name, key_name) {
  this->doc_ = new DynamicJsonDocument(size);
  this->obj_ = this->doc_->createNestedObject();
}

JsonWriter::JsonWriter(size_t size) : Writer() {
  this->doc_ = new DynamicJsonDocument(size);
  this->obj_ = this->doc_->createNestedObject();
}

JsonWriter::~JsonWriter() { delete this->doc_; }

void JsonWriter::Write(const char *value) {
  this->nullCheck_();
  auto obj = this->array_.createNestedObject();
  obj[this->key_name()] = value;
}

void JsonWriter::Write(int value) {
  this->nullCheck_();
  auto obj = this->array_.createNestedObject();
  obj[this->key_name()] = value;
}

void JsonWriter::Write(const char *message, const char *value) {
  char buffer[256];
  snprintf(buffer, sizeof(buffer), "%s %s", message, value);
  this->Write(buffer);
}

void JsonWriter::Write(const char *message, int value) {
  char buffer[256];
  snprintf(buffer, sizeof(buffer), "%s %d", message, value);
  this->Write(buffer);
}

char *JsonWriter::Read(char *output, size_t length) {
  if (this->Length() > 0)
    serializeJson(this->array_, output, length);
  else if (length > 0)
    output[0] = 0;
  return output;
}
