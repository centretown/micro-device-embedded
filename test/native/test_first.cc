// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include <stdio.h>
#include <unity.h>

#include "http_parser.h"        // NOLINT
#include "json_writer.h"        // NOLINT
#include "process_test_data.h"  // NOLINT

// #ifdef UNIT_TEST
/*
char errorBuffer[1024];
void PrintError(ErrorHandler* e) {
  e->err(errorBuffer, sizeof(errorBuffer));
  printf("%s\n", errorBuffer);
}

void test_html_parse(void) {
  JsonWriter writer(1024);
  HttpParser parser(&writer);
  parser.Parse(http_test_data);
  // POST /process/replace HTTP/1.1
  TEST_ASSERT_EQUAL_STRING("POST", parser.method());
  TEST_ASSERT_EQUAL_STRING("/process/replace", parser.path());
  TEST_ASSERT_EQUAL_STRING("HTTP/1.1", parser.version());
  // Content-Length: 688
  TEST_ASSERT_EQUAL(688, strlen(parser.body()));
  PrintError(&parser);
}

void test_html_parse1(void) {
  JsonWriter writer(1024);
  HttpParser parser(&writer);
  parser.Parse(http_bad_method);
  PrintError(&parser);
}

void test_json_writer(void) {
  JsonWriter writer(1024);
  writer.WriteError("hello world");
  writer.WriteError("you made a mistake");
  writer.Write("this is good.");
  writer.ReadAll(errorBuffer, sizeof(errorBuffer));
  printf("%s\n", errorBuffer);
}

int main() {
  UNITY_BEGIN();  // IMPORTANT LINE!
  RUN_TEST(test_json_writer);
  // RUN_TEST(test_html_parse);
  // RUN_TEST(test_html_parse1);

  UNITY_END();  // stop unit testing
}

// #endif  // UNIT_TEST
*/
