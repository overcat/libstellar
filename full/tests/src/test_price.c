#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/price.h"
#include <cmocka.h>

void test_price_to_xdr_object(void **state) {
  struct Price in = {.n = 1, .d = 2};
  stellarxdr_Price out;
  assert_true(price_to_xdr_object(&in, &out));
  assert_int_equal(out.n, 1);
  assert_int_equal(out.d, 2);
}

void test_price_from_xdr_object(void **state) {
  stellarxdr_Price in = {.n = 1, .d = 2};
  struct Price out;
  assert_true(price_from_xdr_object(&in, &out));
  assert_int_equal(out.n, 1);
  assert_int_equal(out.d, 2);
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_price_to_xdr_object),
      cmocka_unit_test(test_price_from_xdr_object),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
