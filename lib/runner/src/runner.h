// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#if defined(ARDUINO)
#pragma once
// create a runnable class derived from parser T
template <class T>
class Runner {
 public:
  explicit Runner(T* parser) { this->parser_ = parser; }
  virtual ~Runner() {}
  virtual void Run() = 0;

  inline T* parser() { return this->parser_; }

 private:
  T* parser_ = NULL;
};
#endif  // ARDUINO
