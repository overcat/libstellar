#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/operation.h"
#include <cmocka.h>

void test_bump_sequence(void **state) {
  struct Operation operation = {.source_account_present = false,
                                .type = BUMP_SEQUENCE,
                                .bump_sequence_op = {.bump_to = 1234567890}};
  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  assert_null(to.sourceAccount);
  assert_int_equal(to.body.type, stellarxdr_BUMP_SEQUENCE);
  assert_int_equal(to.body.stellarxdr_OperationBody_u.bumpSequenceOp.bumpTo,
                   1234567890);

  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  assert_false(from.source_account_present);
  assert_int_equal(from.type, BUMP_SEQUENCE);
  assert_int_equal(from.bump_sequence_op.bump_to, 1234567890);

  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(operation_to_xdr(&operation, &buf, &buf_size));
  char xdr[] = {0x0, 0x0, 0x0, 0x0, 0x0,  0x0,  0x0, 0xb,
                0x0, 0x0, 0x0, 0x0, 0x49, 0x96, 0x2, 0xd2};
  assert_memory_equal(buf, xdr, 16);
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_bump_sequence),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
