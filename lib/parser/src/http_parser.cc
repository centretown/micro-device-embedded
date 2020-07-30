// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <http_parser.h>
#include <http_text.h>
#include <my_strings.h>
#include <stdlib.h>

static const char* kContentLength = "Content-Length:";
static const char* kMalFormedFirst = "JSON missing first '{'";
static const char* kMalFormedLast = "JSON missing last '}'";
static const char* kPost = "POST";

// Parses an http post request, verifies and stores
// the method, path, version and body of the request
void HttpParser::Parse(const Text& text) {
  const char* buffer = text.buffer_;
  auto sourceLength = strlen(buffer);
  auto writer = this->writer();

  if (sourceLength == 0) {
    writer->Write("No Source:");
    return;
  }
  // ensure no overflows, be wary of a long path
  auto len = indexOf(buffer, "\n");
  if (len < 0 || len > args()->MaxLineLength) {
    writer->Write("Header's first line too long:", len);
    return;
  }
  auto args = this->args();

  sscanf(buffer, "%7s %99s %15s\n", args->method_, args->path_, args->version_);
  if (strcmp(kPost, args->method()) != 0) {
    writer->Write("Method must be POST:", args->method());
    return;
  }

  // find content length
  const char* plenText = strstr(buffer, kContentLength);
  if (plenText == NULL) {
    writer->Write(kContentLength, "missing");
    return;
  }
  plenText += strlen(kContentLength);
  auto numLength = indexOf(plenText, "\n");
  if (numLength <= 0) {
    writer->Write(kContentLength, "requires terminating line feed");
    return;
  }

  char lenBuf[12];
  copyString(lenBuf, plenText, sizeof(lenBuf));
  auto contentLength = atoi(lenBuf);
  if (contentLength <= 0) {
    writer->Write(kContentLength, contentLength);
    return;
  }

  const char* body = buffer + sourceLength - contentLength;
  char lbrace[8] = {0};
  sscanf(body, "%3s", lbrace);
  if (lbrace[0] != '{') {
    writer->Write(kMalFormedFirst);
  }

  const char* rbrace = strrchr(body, '}');
  if (rbrace == NULL) {
    writer->Write(kMalFormedLast);
    return;
  }

  args->body_ = body;
  return;
}
