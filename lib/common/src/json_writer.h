// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#include <ArduinoJson.h>

#include "writer.h"  // NOLINT

class JsonWriter : public Writer {
 public:
  explicit JsonWriter(size_t size);
  ~JsonWriter();

  void WriteData(const char *) override;
  void WriteError(const char *) override;
  void WriteError(const char *, int) override;
  void WriteError(const char *, const char *) override;
  char *ReadData(char *output, size_t outputSize) override;
  char *ReadError(char *output, size_t outputSize) override;

 private:
  DynamicJsonDocument *doc_ = NULL;
  JsonObject obj_;
  JsonArray errors_;
  JsonArray data_;
};
