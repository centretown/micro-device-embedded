// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once
#include <string.h>

int indexOf(const char* source, size_t start, const char* find);
int indexOf(const char* source, const char* find);
// ensure padding with at least 1 null terminator
inline char* copyString(char* destination, const char* source, size_t length) {
  return strncpy(destination, source, length - 1);
}
