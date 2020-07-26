// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

class Writer {
 public:
  Writer() {}
  virtual ~Writer() {}

  virtual void WriteData(const char *) = 0;
  virtual void WriteError(const char *) = 0;
  virtual void WriteError(const char *, const int) = 0;
  virtual void WriteError(const char *, const char *) = 0;
  virtual char *ReadData(char *output, size_t outputSize) = 0;
  virtual char *ReadError(char *output, size_t outputSize) = 0;
};
