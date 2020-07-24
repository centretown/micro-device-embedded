// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

#include "parser.h"  // NOLINT
#include "reader.h"  // NOLINT

class ActionParser : public Parser {
 public:
  ActionParser() : Parser() {}
  ~ActionParser() { delete this->parser_; }

  // accessors
  inline int sequence() { return this->sequence_; }
  inline void set_sequence(int sequence) { this->sequence_ = sequence; }

  inline char type() { return this->type_; }
  inline void set_type(char type) { this->type_ = tolower(type); }

  inline Parser* parser() { return this->parser_; }
  inline void set_parser(Parser* parser) { this->parser_ = parser; }

  // command overrides
  void Parse(const JsonObject& obj) override;

 private:
  int sequence_ = 0;
  char type_ = '\0';
  Parser* parser_;
};
