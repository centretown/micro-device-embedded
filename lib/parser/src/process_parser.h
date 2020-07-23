// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once
#include <ArduinoJson.h>

#include "action_parser.h"  // NOLINT
#include "parser.h"         // NOLINT

class ProcessParser : public Parser {
 public:
  ProcessParser() {}
  ~ProcessParser() {
    delete[] this->setup_;
    delete[] this->loop_;
  }

  void Parse(const JsonObject& obj) override;
  ActionParser** ParseActions(const JsonArray& arr, size_t len);

  inline String label() { return this->label_; }
  inline void set_label(String label) { this->label_ = label; }

  inline String deviceKey() { return this->deviceKey_; }
  inline void set_deviceKey(String deviceKey) { this->deviceKey_ = deviceKey; }

  inline String purpose() { return this->purpose_; }
  inline void set_purpose(String purpose) { this->purpose_ = purpose; }

  inline ActionParser** setup() { return this->setup_; }
  inline void set_setup(ActionParser** setup) { this->setup_ = setup; }
  inline size_t setup_length() { return this->setup_length_; }
  inline void set_setup_length(size_t length) { this->setup_length_ = length; }

  inline ActionParser** loop() { return this->loop_; }
  inline void set_loop(ActionParser** loop) { this->loop_ = loop; }
  inline size_t loop_length() { return this->loop_length_; }
  inline void set_loop_length(size_t length) { this->loop_length_ = length; }

 private:
  String label_;
  String deviceKey_;
  String purpose_;
  ActionParser** setup_ = NULL;
  size_t setup_length_ = 0;
  ActionParser** loop_ = NULL;
  size_t loop_length_ = 0;
};
