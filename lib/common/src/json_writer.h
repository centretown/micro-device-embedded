// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <ArduinoJson.h>
#include <writer.h>

class JsonWriter : public Writer {
 public:
  explicit JsonWriter(size_t size);
  explicit JsonWriter(size_t size, const char *array_name,
                      const char *key_name);
  ~JsonWriter();

  void Write(const char *value) override;
  void Write(int value) override;
  void Write(const char *message, int value) override;
  void Write(const char *message, const char *value) override;
  char *Read(char *output, size_t length) override;
  size_t Length() override { return this->array_.size(); }

 private:
  DynamicJsonDocument *doc_ = NULL;
  JsonObject obj_;
  JsonArray array_;

  void nullCheck_() {
    if (this->array_.isNull()) {
      this->array_ = this->obj_.createNestedArray(this->array_name());
    }
  }
};
