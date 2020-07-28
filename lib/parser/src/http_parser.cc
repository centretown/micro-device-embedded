// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <http_parser.h>
#include <http_text.h>
#include <my_strings.h>
#include <stdlib.h>

static const char* kContentLength = "Content-Length: ";
const char* kPost = "POST";

// Parses an http post request, verifies and stores
// the method, path, version and body of the request
void HttpParser::Parse(const Text& text) {
  const char* buffer = text.buffer_;
  auto sourceLength = strlen(buffer);

  if (sourceLength == 0) {
    this->WriteError("No Source:");
    return;
  }
  // ensure no overflows, be wary of a long path
  auto len = indexOf(buffer, "\n");
  if (len < 0 || len > args()->MaxLineLength) {
    this->WriteError("Header's first line too long:", len);
    return;
  }
  auto args = this->args();

  sscanf(buffer, "%s %s %s\n", args->method_, args->path_, args->version_);
  if (strcmp(kPost, args->method()) != 0) {
    this->WriteError("Method must be POST:", args->method());
    return;
  }

  // find content length
  const char* plenText = strstr(buffer, kContentLength);
  if (plenText == NULL) {
    this->WriteError(kContentLength, " missing");
    return;
  }
  plenText += strlen(kContentLength);
  auto numLength = indexOf(plenText, "\n");
  if (numLength <= 0) {
    this->WriteError(kContentLength, " requires terminating line feed");
    return;
  }

  char lenBuf[12];
  copyString(lenBuf, plenText, sizeof(lenBuf));
  auto contentLength = atoi(lenBuf);
  if (contentLength <= 0) {
    this->WriteError(kContentLength, " requires terminating line feed");
    return;
  }

  args->body_ = buffer + sourceLength - contentLength;

  return;
}
