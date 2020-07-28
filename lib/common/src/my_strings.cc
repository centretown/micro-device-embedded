// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <my_strings.h>

int indexOf(const char* source, const char* find) {
  auto result = strstr(source, find);
  if (result > source) {
    return result - source;
  }
  return -1;
}

int indexOf(const char* source, size_t offset, const char* find) {
  if (offset > strlen(source)) {
    return 0;
  }
  return indexOf(source + offset, find);
}
