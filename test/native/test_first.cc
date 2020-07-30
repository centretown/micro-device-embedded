// Copyright 2020 Dave Marsh. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

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

char readBuffer[4096];
char errBuffer[2048];

void test_good_process(void) {
  JsonWriter writer(1024);

  HttpText httpText;
  HttpParser* httpParser = BuildHttpParser(http_test_data, &writer, &httpText);
  TEST_ASSERT(true == httpParser->ok());
  auto args = httpParser->args();
  TEST_ASSERT_EQUAL_PTR(&httpText, args);
  TEST_ASSERT_EQUAL_STRING("POST", httpText.method());
  TEST_ASSERT_EQUAL_STRING("/process/replace", httpText.path());
  TEST_ASSERT_EQUAL_STRING("HTTP/1.1", httpText.version());
  TEST_ASSERT_EQUAL(778, strlen(httpText.body()));
  printf("body length: %lu\n", strlen(httpText.body()));

  delete httpParser;

  Process* process = new Process();
  ProcessParser* processParser =
      BuildProcessParser(httpText.body(), &writer, process);

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

  TEST_ASSERT_EQUAL_UINT(5, process->loop_length());
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

  ProcessRunner* processRunner = new ProcessRunner(process, &writer);
  for (auto i = 0; i < 3; ++i) processRunner->Run();
  delete processRunner;
  delete process;
}

static const char expected_bad_method[] =
    R"~~([{"result":"Method must be POST: GET"}])~~";
void test_bad_method(void) {
  JsonWriter writer(1024);
  HttpText httpText;
  HttpParser parser(&writer, &httpText);
  Text text(http_bad_method);
  parser.Parse(text);
  TEST_ASSERT(false == parser.ok());
  writer.Read(errBuffer, sizeof(errBuffer));
  printf("%s\n", errBuffer);
  TEST_ASSERT(0 == strcmp(expected_bad_method, errBuffer))
}

void test_json_writer(void) {
  JsonWriter writer(1024);

  writer.Write("hello world");
  writer.Write("you made a mistake");
  printf("%s\n", writer.Read(errBuffer, sizeof(errBuffer)));

  writer.Write("this is good.");
  printf("%s\n", writer.Read(errBuffer, sizeof(errBuffer)));
}

int main() {
  UNITY_BEGIN();  // IMPORTANT LINE!

  RUN_TEST(test_json_writer);
  RUN_TEST(test_good_process);
  RUN_TEST(test_bad_method);

  UNITY_END();  // stop unit testing
}

// #endif  // UNIT_TEST
