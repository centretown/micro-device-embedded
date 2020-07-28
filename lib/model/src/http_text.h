// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

class HttpText {
 public:
  HttpText() {}
  ~HttpText() {}
  inline const char* path() { return this->path_; }
  inline const char* version() { return this->version_; }
  inline const char* method() { return this->method_; }
  inline const char* body() { return this->body_; }
  const size_t MaxLineLength =
      sizeof(path_) + sizeof(version_) + sizeof(method_);

  char path_[100] = {0};
  char version_[16] = {0};
  char method_[8] = {0};
  const char* body_ = NULL;
};
