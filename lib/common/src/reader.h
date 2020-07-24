// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#pragma once
#include <ArduinoJson.h>

class Reader {
 public:
  Reader();
  virtual ~Reader();

  virtual char* Read(char* key) = 0;
  virtual int ReadInt(char* key) = 0;
};
