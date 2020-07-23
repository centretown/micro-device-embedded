// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#include <ArduinoJson.h>

#include "parser.h"  // NOLINT

class ActionParser : public Parser {
 public:
  ActionParser() {}
  ~ActionParser() { delete this->parser_; }

  // accessors
  inline int sequence() { return this->sequence_; }
  inline void set_sequence(int sequence) { this->sequence_ = sequence; }

  inline char type() { return this->type_; }
  inline void set_type(String type) { this->type_ = type.charAt(0); }

  inline Parser* parser() { return this->parser_; }
  inline void set_parser(Parser* parser) { this->parser_ = parser; }

  // command overrides
  void Parse(const JsonObject& obj) override;

  // returns an Action command pointer that acts as a NOP
  static ActionParser* NoAction();

 private:
  int sequence_ = 0;
  char type_ = '\0';
  Parser* parser_;
};
