// Copyright 2020, Dave Marsh, Centretown
// All rights reserved. see LICENSE.TXT

#include <unity.h>

#ifdef UNIT_TEST

void test_test() { TEST_ASSERT_EQUAL(true, true); }

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

#endif  // UNIT_TEST
