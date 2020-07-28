// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include <stdio.h>
#include <unity.h>

#include "http_parser.h"        // NOLINT
#include "json_writer.h"        // NOLINT
#include "process_test_data.h"  // NOLINT
#include "text.h"               // NOLINT

char readBuffer[4096];
char errBuffer[2048];

static const char expected_bad_method[] =
    R"~~([{"message":"Method must be POST: GET"}])~~";
void test_good_process(void) {
  JsonWriter writer(1024);
  HttpText httpText;
  HttpParser parser(&writer, &httpText);
  Text text(http_test_data);
  parser.Parse(text);
  if (parser.ok()) {
    auto args = parser.args();
    // POST /process/replace HTTP/1.1
    TEST_ASSERT_EQUAL_STRING("POST", args->method());
    TEST_ASSERT_EQUAL_STRING("/process/replace", args->path());
    TEST_ASSERT_EQUAL_STRING("HTTP/1.1", args->version());
    // Content-Length: 688
    TEST_ASSERT_EQUAL(688, strlen(args->body()));
    // PrintError(&parser);
  }
}

void test_bad_method(void) {
  JsonWriter writer(1024);
  HttpText httpText;
  HttpParser parser(&writer, &httpText);
  Text text(http_bad_method);
  parser.Parse(text);
  TEST_ASSERT(false == parser.ok());
  printf("%s\n", writer.ReadError(errBuffer, sizeof(errBuffer)));
  TEST_ASSERT(0 == strcmp(expected_bad_method, errBuffer))
}

void test_json_writer(void) {
  JsonWriter writer(1024);

  writer.WriteError("hello world");
  writer.WriteError("you made a mistake");
  printf("%s\n", writer.ReadError(errBuffer, sizeof(errBuffer)));

  writer.WriteData("this is good.");
  printf("%s\n", writer.ReadData(errBuffer, sizeof(errBuffer)));
}

int main() {
  UNITY_BEGIN();  // IMPORTANT LINE!

  RUN_TEST(test_json_writer);
  RUN_TEST(test_good_process);
  RUN_TEST(test_bad_method);

  UNITY_END();  // stop unit testing
}

// #endif  // UNIT_TEST
