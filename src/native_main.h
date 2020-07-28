// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <builder.h>
#include <http_parser.h>
#include <json_writer.h>
#include <process_parser.h>
#include <process_runner.h>
#include <process_test_data.h>
#include <stdio.h>

ProcessRunner* processRunner = NULL;

char readBuffer[4096];
char errBuffer[2048];
const char* kOverflow = "Read Buffer overflow";

int main(int argc, char* argv[]) {
  JsonWriter* writer = new JsonWriter(1024);

  // parse http
  HttpText httpText;
  HttpParser* request = BuildHttpParser(http_test_data, writer, &httpText);
  if (request->ok() == false) {
    printf("%s\n", request->ReadError(errBuffer, sizeof(errBuffer)));
    return 0;
  }

  printf("%s\n%s\n%s %s %s\n", "http parsed...", httpText.body(),
         httpText.method(), httpText.path(), httpText.version());
  // return 0;

  Process* process = new Process();
  ProcessParser* parser = BuildProcessParser(httpText.body(), writer, process);
  if (parser->ok() == false) {
    printf("%s\n", request->ReadError(errBuffer, sizeof(errBuffer)));
    return 0;
  }
  printf("%s", "process parsed...\n");

  delete processRunner;
  processRunner = new ProcessRunner(process);
  printf("%s\n", "process runner built...\n");
  processRunner->Run();
  return 0;
}
