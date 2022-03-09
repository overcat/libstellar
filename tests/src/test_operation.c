#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/operation.h"
#include <cmocka.h>

void test_create_account(void **state) {
  char *destination =
      "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO";
  struct Operation operation = {
      .source_account_present = false,
      .type = CREATE_ACCOUNT,
      .createAccountOp = {.destination = destination,
                          .startingBalance = 10000000}};
  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  assert_null(to.sourceAccount);
  assert_int_equal(to.body.type, stellarxdr_CREATE_ACCOUNT);
  assert_int_equal(
      to.body.stellarxdr_OperationBody_u.createAccountOp.startingBalance,
      10000000);

  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  assert_false(from.source_account_present);
  assert_int_equal(from.type, CREATE_ACCOUNT);
  assert_int_equal(from.createAccountOp.startingBalance, 10000000);
  assert_memory_equal(from.createAccountOp.destination, destination, 32);

  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(operation_to_xdr(&operation, &buf, &buf_size));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                0x0,  0x0,  0x0,  0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff,
                0x7,  0x57, 0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74,
                0x46, 0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd,
                0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12, 0x0,
                0x0,  0x0,  0x0,  0x0,  0x98, 0x96, 0x80};
  assert_int_equal(buf_size, 52);
  assert_memory_equal(buf, xdr, buf_size);
}

void test_payment(void **state) {
  char *destination =
      "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO";
  struct Asset asset = {.type = ASSET_TYPE_NATIVE};

  struct Operation operation = {.source_account_present = false,
                                .type = PAYMENT,
                                .paymentOp = {.destination = destination,
                                              .asset = asset,
                                              .amount = 10000000}};
  stellarxdr_Operation to;

  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(operation_to_xdr(&operation, &buf, &buf_size));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x0,  0x0,
                0x0,  0x0,  0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57,
                0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46, 0xa5, 0xc9,
                0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd, 0xfc, 0x74, 0xdb, 0x7d,
                0x6e, 0x1d, 0x9d, 0x12, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                0x0,  0x0,  0x0,  0x98, 0x96, 0x80};
  assert_int_equal(buf_size, 56);
  assert_memory_equal(buf, xdr, buf_size);
}

void test_payment_with_muxed_account(void **state) {
  char *destination =
      "MB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWOREAAAAAAAAAAAAFR3G";
  struct Asset asset = {.type = ASSET_TYPE_NATIVE};

  struct Operation operation = {.source_account_present = false,
                                .type = PAYMENT,
                                .paymentOp = {.destination = destination,
                                              .asset = asset,
                                              .amount = 10000000}};
  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(operation_to_xdr(&operation, &buf, &buf_size));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x0,  0x0,
                0x1,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,
                0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57, 0x3b, 0x97,
                0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46, 0xa5, 0xc9, 0x30, 0x5f,
                0x99, 0x49, 0x6,  0xbd, 0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d,
                0x9d, 0x12, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                0x0,  0x98, 0x96, 0x80};
  assert_int_equal(buf_size, 64);
  assert_memory_equal(buf, xdr, buf_size);
}

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
      cmocka_unit_test(test_create_account),
      cmocka_unit_test(test_payment),
      cmocka_unit_test(test_payment_with_muxed_account),
      cmocka_unit_test(test_bump_sequence),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
