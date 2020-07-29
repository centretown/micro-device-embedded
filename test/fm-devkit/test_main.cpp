// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include <Arduino.h>
#include <builder.h>
#include <delay_runner.h>
#include <http_parser.h>
#include <json_writer.h>
#include <mode_runner.h>
#include <pin_runner.h>
#include <process.h>
#include <process_parser.h>
#include <process_runner.h>
#include <process_test_data.h>
#include <stdio.h>
#include <text.h>
#include <unity.h>

ProcessRunner* processRunner = NULL;
Process* process = NULL;

void setup() {
  // Start Serial
  Serial.begin(9600);
  UNITY_BEGIN();
  JsonWriter writer(1024);

  HttpText httpText;
  HttpParser* httpParser = BuildHttpParser(http_test_data, &writer, &httpText);
  TEST_ASSERT(true == httpParser->ok());
  auto args = httpParser->args();
  TEST_ASSERT_EQUAL_STRING("POST", args->method());
  TEST_ASSERT_EQUAL_STRING("/process/replace", args->path());
  TEST_ASSERT_EQUAL_STRING("HTTP/1.1", args->version());
  TEST_ASSERT_EQUAL(688, strlen(args->body()));
  delete httpParser;

  Process* replaceProcess = new Process();
  ProcessParser* processParser =
      BuildProcessParser(httpText.body(), &writer, replaceProcess);
  TEST_ASSERT(true == processParser->ok());
  TEST_ASSERT_EQUAL_STRING("Process 1", process->label());
  TEST_ASSERT_EQUAL_STRING("esp32-200", process->deviceKey());
  TEST_ASSERT_EQUAL_STRING("Blink", process->purpose());
  delete processParser;

  TEST_ASSERT_EQUAL_UINT(1, process->setup_length());
  auto setup = process->setup();

  ModeRunner* mr = reinterpret_cast<ModeRunner*>(setup[0]);
  auto mode = mr->args();
  TEST_ASSERT_EQUAL_INT(2, mode->pin());
  TEST_ASSERT_EQUAL_CHAR('o', mode->mode());
  TEST_ASSERT_EQUAL_CHAR('d', mode->signal());

  TEST_ASSERT_EQUAL_UINT(4, process->loop_length());
  auto loop = process->loop();

  PinRunner* pr = reinterpret_cast<PinRunner*>(loop[0]);
  auto pin = pr->args();
  TEST_ASSERT_EQUAL_INT(2, pin->pin());
  TEST_ASSERT_EQUAL_CHAR('o', pin->mode());
  TEST_ASSERT_EQUAL_CHAR('d', pin->signal());
  TEST_ASSERT_EQUAL_INT(1, pin->value());

  DelayRunner* dr = reinterpret_cast<DelayRunner*>(loop[1]);
  auto delay = dr->args();
  TEST_ASSERT_EQUAL_INT(200, delay->duration());

  pr = reinterpret_cast<PinRunner*>(loop[2]);
  pin = pr->args();
  TEST_ASSERT_EQUAL_INT(2, pin->pin());
  TEST_ASSERT_EQUAL_CHAR('o', pin->mode());
  TEST_ASSERT_EQUAL_CHAR('d', pin->signal());
  TEST_ASSERT_EQUAL_INT(0, pin->value());

  dr = reinterpret_cast<DelayRunner*>(loop[3]);
  delay = dr->args();
  TEST_ASSERT_EQUAL_INT(500, delay->duration());

  delete process;
  process = replaceProcess;
  delete processRunner;
  processRunner = new ProcessRunner(process);
  // processRunner->Run();
  processRunner->RunOps(process->setup(), process->setup_length());

  for (auto i = 0; i < 10; i++)
    processRunner->RunOps(process->loop(), process->loop_length());
}

void loop() {
  processRunner->Run();
  UNITY_END();  // stop unit testing
}
