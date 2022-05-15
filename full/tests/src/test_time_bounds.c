#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/time_bounds.h"
#include <cmocka.h>

void test_time_bounds_to_xdr_object(void **state) {
  struct TimeBounds in = {.max_time = 1632884859, .min_time = 0};
  stellarxdr_TimeBounds out;
  assert_true(time_bounds_to_xdr_object(&in, &out));
  assert_int_equal(out.maxTime, 1632884859);
  assert_int_equal(out.minTime, 0);
}

void test_time_bounds_from_xdr_object(void **state) {
  stellarxdr_TimeBounds in = {.maxTime = 1632884859, .minTime = 0};
  struct TimeBounds out;
  assert_true(time_bounds_from_xdr_object(&in, &out));
  assert_int_equal(out.max_time, 1632884859);
  assert_int_equal(out.min_time, 0);
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_time_bounds_to_xdr_object),
      cmocka_unit_test(test_time_bounds_from_xdr_object),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
