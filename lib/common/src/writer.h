// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once

class Writer {
 public:
  Writer() {}
  virtual ~Writer() {}

  virtual void Write(const char *) = 0;
  virtual void WriteError(const char *) = 0;
  virtual void WriteError(const char *, const int) = 0;
  virtual void WriteError(const char *, const char *) = 0;
  virtual void ReadAll(char *output, size_t outputSize) = 0;
};
