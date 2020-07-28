// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <ArduinoJson.h>

#include "parser.h"  // NOLINT
#include "writer.h"  // NOLINT

template <class T>
class JsonObjectParser : public Parser<T, JsonObject> {
 public:
  explicit JsonObjectParser(Writer* writer, T* args)
      : Parser<T, JsonObject>(writer, args) {}
  ~JsonObjectParser() {}
};
