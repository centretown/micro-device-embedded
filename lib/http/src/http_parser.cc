// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include "http_parser.h"  // NOLINT

#include "my_strings.h"  // NOLINT

static const char* kContentLength = "Content-Length: ";
const char* kPost = "POST";

// Parses an http post request, verifies and stores
// the method, path, version and body of the request
void HttpParser::Parse(char* source) {
  auto sourceLength = strlen(source);
  if (sourceLength == 0) {
    this->AppendError("No Source: ");
    return;
  }

  // ensure no overflows, be wary of a long path
  auto len = indexOf(source, "\n");
  if (len < 0 || len > 128) {
    this->AppendError("Header's first line too long: ", len);
    return;
  }

  sscanf(source, "%s %s %s\n", this->method_, this->path_, this->version_);
  if (strcmp(kPost, this->method()) != 0) {
    this->AppendError("Method must be POST: ", this->method());
    return;
  }

  // find content length
  char* plenText = strstr(source, kContentLength);
  if (plenText == NULL) {
    this->AppendError(kContentLength, " missing");
    return;
  }
  plenText += strlen(kContentLength);
  auto numLength = indexOf(plenText, "\n");
  if (numLength <= 0) {
    this->AppendError(kContentLength, " requires terminating line feed");
    return;
  }

  char lenBuf[12];
  strncpy(lenBuf, plenText, numLength);
  auto contentLength = toInt(lenBuf);
  if (contentLength <= 0) {
    this->AppendError(kContentLength, " requires terminating line feed");
    return;
  }

  this->body_ = source + sourceLength - contentLength;
}
