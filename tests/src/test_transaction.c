#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/memo.h"
#include "../../src/muxed_account.h"
#include "../../src/transaction.h"
#include <cmocka.h>
bool _transaction_to_xdr(const struct Transaction *in, char **buf,
                         size_t *buf_size) {
  stellarxdr_Transaction transaction_xdr;
  if (!transaction_to_xdr_object(in, &transaction_xdr)) {
    return false;
  }
  FILE *fp = open_memstream(buf, buf_size);
  XDR xdr;
  xdrstdio_create(&xdr, fp, XDR_ENCODE);
  if (!xdr_stellarxdr_Transaction(&xdr, &transaction_xdr)) {
    fclose(fp);
    return false;
  }
  fclose(fp);
  return true;
}

bool _transaction_from_xdr(char *buf, size_t buf_size,
                           struct Transaction *out) {
  FILE *fp = fmemopen(buf, buf_size, "r");
  XDR xdr;
  stellarxdr_Transaction *transaction_xdr =
      malloc(sizeof(stellarxdr_Transaction));
  xdrstdio_create(&xdr, fp, XDR_DECODE);
  if (!xdr_stellarxdr_Transaction(&xdr, transaction_xdr)) {
    fclose(fp);
    return false;
  }
  if (!transaction_from_xdr_object(transaction_xdr, out)) {
    return false;
  }
  fclose(fp);
  return true;
}

void test_transaction_to_xdr_object(void **state) {
  char *account = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO";
  struct MuxedAccount muxed_account;
  assert_true(muxed_account_from_address(account, &muxed_account));
  struct Memo memo;
  memo_text(&memo, "Hello, Stellar!");
  struct TimeBounds time_bounds = {.max_time = 1632884859, .min_time = 0};
  struct Operation operation[1] = {
      {.source_account_present = false,
       .type = BUMP_SEQUENCE,
       .bump_sequence_op = {.bump_to = 1234567890}}};
  struct Transaction transaction = {.source_account = muxed_account,
                                    .base_fee = 100,
                                    .sequence_number = 1234567890,
                                    .memo = memo,
                                    .time_bounds = &time_bounds,
                                    .operations_len = 1,
                                    .operations = operation};

  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(_transaction_to_xdr(&transaction, &buf, &buf_size));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57,
      0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46, 0xa5, 0xc9, 0x30, 0x5f,
      0x99, 0x49, 0x6,  0xbd, 0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12,
      0x0,  0x0,  0x0,  0x64, 0x0,  0x0,  0x0,  0x0,  0x49, 0x96, 0x2,  0xd2,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x0,  0x61, 0x53, 0xd8, 0x7b, 0x0,  0x0,  0x0,  0x1,
      0x0,  0x0,  0x0,  0xf,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x53,
      0x74, 0x65, 0x6c, 0x6c, 0x61, 0x72, 0x21, 0x0,  0x0,  0x0,  0x0,  0x1,
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xb,  0x0,  0x0,  0x0,  0x0,
      0x49, 0x96, 0x2,  0xd2, 0x0,  0x0,  0x0,  0x0};
  assert_memory_equal(buf, xdr, 116);
}

void test_transaction_to_xdr_object_without_time_bounds(void **state) {
  char *account = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO";
  struct MuxedAccount muxed_account;
  assert_true(muxed_account_from_address(account, &muxed_account));
  struct Memo memo;
  memo_text(&memo, "Hello, Stellar!");
  struct Operation operation[1] = {
      {.source_account_present = false,
       .type = BUMP_SEQUENCE,
       .bump_sequence_op = {.bump_to = 1234567890}}};
  struct Transaction transaction = {.source_account = muxed_account,
                                    .base_fee = 100,
                                    .sequence_number = 1234567890,
                                    .memo = memo,
                                    .time_bounds = NULL,
                                    .operations_len = 1,
                                    .operations = operation};

  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(_transaction_to_xdr(&transaction, &buf, &buf_size));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff,
                0x7,  0x57, 0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46,
                0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd, 0xfc, 0x74,
                0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12, 0x0,  0x0,  0x0,  0x64,
                0x0,  0x0,  0x0,  0x0,  0x49, 0x96, 0x2,  0xd2, 0x0,  0x0,
                0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0xf,
                0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x53, 0x74, 0x65,
                0x6c, 0x6c, 0x61, 0x72, 0x21, 0x0,  0x0,  0x0,  0x0,  0x1,
                0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xb,  0x0,  0x0,
                0x0,  0x0,  0x49, 0x96, 0x2,  0xd2, 0x0,  0x0,  0x0,  0x0};
  assert_memory_equal(buf, xdr, 100);
}

void test_transaction_to_xdr_object_multi_op(void **state) {
  char *account = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO";
  struct MuxedAccount muxed_account;
  assert_true(muxed_account_from_address(account, &muxed_account));
  struct Memo memo;
  memo_text(&memo, "Hello, Stellar!");
  struct TimeBounds time_bounds = {.max_time = 1, .min_time = 1};
  struct Operation operation[2] = {
      {.source_account_present = false,
       .type = BUMP_SEQUENCE,
       .bump_sequence_op = {.bump_to = 1234567890}},
      {.source_account_present = false,
       .type = BUMP_SEQUENCE,
       .bump_sequence_op = {.bump_to = 1234567891}}};
  struct Transaction transaction = {.source_account = muxed_account,
                                    .base_fee = 100,
                                    .sequence_number = 1234567890,
                                    .memo = memo,
                                    .time_bounds = &time_bounds,
                                    .operations_len = 2,
                                    .operations = operation};

  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(_transaction_to_xdr(&transaction, &buf, &buf_size));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57,
      0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46, 0xa5, 0xc9, 0x30, 0x5f,
      0x99, 0x49, 0x6,  0xbd, 0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12,
      0x0,  0x0,  0x0,  0xc8, 0x0,  0x0,  0x0,  0x0,  0x49, 0x96, 0x2,  0xd2,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x1,
      0x0,  0x0,  0x0,  0xf,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x2c, 0x20, 0x53,
      0x74, 0x65, 0x6c, 0x6c, 0x61, 0x72, 0x21, 0x0,  0x0,  0x0,  0x0,  0x2,
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xb,  0x0,  0x0,  0x0,  0x0,
      0x49, 0x96, 0x2,  0xd2, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xb,
      0x0,  0x0,  0x0,  0x0,  0x49, 0x96, 0x2,  0xd3, 0x0,  0x0,  0x0,  0x0};
  assert_memory_equal(buf, xdr, 132);
}

void test_transaction_from_xdr_object(void **state) {
  char *account = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO";
  struct MuxedAccount muxed_account;
  assert_true(muxed_account_from_address(account, &muxed_account));
  struct Memo memo;
  memo_text(&memo, "Hello, Stellar!");
  struct TimeBounds time_bounds = {.max_time = 1632884859, .min_time = 0};
  struct Operation operation[1] = {
      {.source_account_present = false,
       .type = BUMP_SEQUENCE,
       .bump_sequence_op = {.bump_to = 1234567890}}};
  struct Transaction transaction = {.source_account = muxed_account,
                                    .base_fee = 100,
                                    .sequence_number = 1234567890,
                                    .memo = memo,
                                    .time_bounds = &time_bounds,
                                    .operations_len = 1,
                                    .operations = operation};

  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(_transaction_to_xdr(&transaction, &buf, &buf_size));

  struct Transaction out;
  assert_true(_transaction_from_xdr(buf, buf_size, &out));

  char *buf2 = NULL;
  size_t buf_size2 = 0;
  assert_true(_transaction_to_xdr(&out, &buf2, &buf_size2));

  assert_int_equal(buf_size, buf_size2);
  assert_memory_equal(buf, buf2, buf_size);
}

void test_transaction_from_xdr_object_without_time_bounds(void **state) {
  char *account = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO";
  struct MuxedAccount muxed_account;
  assert_true(muxed_account_from_address(account, &muxed_account));
  struct Memo memo;
  memo_text(&memo, "Hello, Stellar!");
  struct Operation operation[1] = {
      {.source_account_present = false,
       .type = BUMP_SEQUENCE,
       .bump_sequence_op = {.bump_to = 1234567890}}};
  struct Transaction transaction = {.source_account = muxed_account,
                                    .base_fee = 100,
                                    .sequence_number = 1234567890,
                                    .memo = memo,
                                    .time_bounds = NULL,
                                    .operations_len = 1,
                                    .operations = operation};

  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(_transaction_to_xdr(&transaction, &buf, &buf_size));

  struct Transaction out;
  assert_true(_transaction_from_xdr(buf, buf_size, &out));

  char *buf2 = NULL;
  size_t buf_size2 = 0;
  assert_true(_transaction_to_xdr(&out, &buf2, &buf_size2));

  assert_int_equal(buf_size, buf_size2);
  assert_memory_equal(buf, buf2, buf_size);
}

void test_transaction_from_xdr_object_multi_op(void **state) {
  char *account = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO";
  struct MuxedAccount muxed_account;
  assert_true(muxed_account_from_address(account, &muxed_account));
  struct Memo memo;
  memo_text(&memo, "Hello, Stellar!");
  struct TimeBounds time_bounds = {.max_time = 1, .min_time = 1};
  struct Operation operation[2] = {
      {.source_account_present = false,
       .type = BUMP_SEQUENCE,
       .bump_sequence_op = {.bump_to = 1234567890}},
      {.source_account_present = false,
       .type = BUMP_SEQUENCE,
       .bump_sequence_op = {.bump_to = 1234567891}}};
  struct Transaction transaction = {.source_account = muxed_account,
                                    .base_fee = 100,
                                    .sequence_number = 1234567890,
                                    .memo = memo,
                                    .time_bounds = &time_bounds,
                                    .operations_len = 2,
                                    .operations = operation};

  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(_transaction_to_xdr(&transaction, &buf, &buf_size));

  struct Transaction out;
  assert_true(_transaction_from_xdr(buf, buf_size, &out));

  char *buf2 = NULL;
  size_t buf_size2 = 0;
  assert_true(_transaction_to_xdr(&out, &buf2, &buf_size2));

  assert_int_equal(buf_size, buf_size2);
  assert_memory_equal(buf, buf2, buf_size);
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_transaction_to_xdr_object),
      cmocka_unit_test(test_transaction_to_xdr_object_without_time_bounds),
      cmocka_unit_test(test_transaction_to_xdr_object_multi_op),
      cmocka_unit_test(test_transaction_from_xdr_object),
      cmocka_unit_test(test_transaction_from_xdr_object_without_time_bounds),
      cmocka_unit_test(test_transaction_from_xdr_object_multi_op),

  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
