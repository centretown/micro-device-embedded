// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include <Arduino.h>
#include <ArduinoJson.h>
#include <unity.h>

#include "../process_test_data.h"

// void setUp(void) {
// // set stuff up here
// }

// void tearDown(void) {
// // clean stuff up here
// }

void test_setup(void) { TEST_ASSERT_EQUAL(true, true); }
void test_loop(void) { TEST_ASSERT_EQUAL(true, true); }

void setup() {
  UNITY_BEGIN();  // IMPORTANT LINE!
  RUN_TEST(test_setup);
}

void loop() {
  RUN_TEST(test_loop);
  UNITY_END();  // stop unit testing
}
