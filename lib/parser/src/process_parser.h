// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once
#include <ArduinoJson.h>

#include "action_parser.h"  // NOLINT
#include "parser.h"         // NOLINT

class ProcessParser : public Parser {
 public:
  ProcessParser() : Parser() {}
  ~ProcessParser() {
    delete[] this->setup_;
    delete[] this->loop_;
  }

  void Parse(const JsonObject& obj) override;
  ActionParser** ParseActions(const JsonArray& arr, size_t len);

  inline char* label() { return this->label_; }
  inline void set_label(const char* label) {
    strncpy(this->label_, label, sizeof(this->label_) - 1);
  }

  inline char* deviceKey() { return this->deviceKey_; }

  inline void set_deviceKey(const char* deviceKey) {
    strncpy(this->deviceKey_, deviceKey, sizeof(this->deviceKey_) - 1);
  }

  inline char* purpose() { return this->purpose_; }
  inline void set_purpose(const char* purpose) {
    strncpy(this->purpose_, purpose, sizeof(this->purpose_) - 1);
  }

  inline ActionParser** setup() { return this->setup_; }
  inline void set_setup(ActionParser** setup) { this->setup_ = setup; }
  inline size_t setup_length() { return this->setup_length_; }
  inline void set_setup_length(size_t length) { this->setup_length_ = length; }

  inline ActionParser** loop() { return this->loop_; }
  inline void set_loop(ActionParser** loop) { this->loop_ = loop; }
  inline size_t loop_length() { return this->loop_length_; }
  inline void set_loop_length(size_t length) { this->loop_length_ = length; }

 private:
  char label_[32];
  char deviceKey_[12];
  char purpose_[128];
  ActionParser** setup_ = NULL;
  size_t setup_length_ = 0;
  ActionParser** loop_ = NULL;
  size_t loop_length_ = 0;
};
