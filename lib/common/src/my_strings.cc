// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include <my_strings.h>

int indexOf(const char* src, const char* find) {
  auto result = strstr(src, find);
  if (result > src) {
    return result - src;
  }
  return -1;
}

int indexOf(const char* src, size_t offset, const char* find) {
  if (offset > strlen(src)) {
    return 0;
  }
  return indexOf(src + offset, find);
}

int toInt(const char* src) { return atoi(src); }
