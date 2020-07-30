// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#pragma once

#include <build_process.h>
#include <http_parser.h>
#include <json_writer.h>
#include <process_parser.h>
#include <process_runner.h>
#include <process_test_data.h>
#include <stdio.h>

ProcessRunner* processRunner = NULL;
Process* process = NULL;

char readBuffer[4096];
char errBuffer[2048];
const char* kOverflow = "Read Buffer overflow";

int main(int argc, char* argv[]) {
  // start blink as default
  JsonWriter* writer = new JsonWriter(1024, "errors", "error");
  processRunner = buildProcess(http_bad_method, writer);
  if (processRunner == NULL) {
    printf("%s\n", writer->Read(errBuffer, sizeof(errBuffer)));
  } else {
    process = processRunner->args();
    processRunner->Run();
  }

  delete writer;
  writer = new JsonWriter(1024);
  processRunner = buildProcess(http_test_data, writer);
  if (processRunner == NULL) {
    printf("%s\n", writer->Read(errBuffer, sizeof(errBuffer)));
  } else {
    writer->set_array_name("results");
    writer->set_key_name("result");
    process = processRunner->args();
    processRunner->Run();
  }

  delete writer;
  delete processRunner;
  delete process;
  return 0;
}
