// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include <build_process.h>
#include <builder.h>
#include <http_parser.h>
#include <process_parser.h>

ProcessRunner* buildProcess(char* readBuffer, Writer* writer) {
  // parse http
  HttpText httpText;
  HttpParser* httpParser = BuildHttpParser(readBuffer, writer, &httpText);
  if (httpParser->ok() == false) {
    delete httpParser;
    return NULL;
  }
  delete httpParser;

  Process* replaceProcess = new Process();
  ProcessParser* processParser =
      BuildProcessParser(httpText.body(), writer, replaceProcess);
  if (processParser->ok() == false) {
    delete processParser;
    return NULL;
  }

  delete processParser;
  return new ProcessRunner(replaceProcess, writer);
}
