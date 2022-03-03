#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/memo.h"
#include "../../src/muxed_account.h"
#include "../../src/network.h"
#include "../../src/transaction.h"
#include "../../src/transaction_envelope.h"
#include <cmocka.h>

void test_transaction_envelope_hash(void **state) {
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

  struct TransactionEnvelope transactionEnvelope = {
      .transaction = transaction,
      .networkPassphrase = PUBLIC_NETWORK_PASSPHRASE,
  };
  char expect_hash[] = {0xcc, 0xe5, 0x23, 0xc6, 0x78, 0xab, 0x41, 0x89,
                        0x2c, 0x2b, 0xa7, 0x1e, 0x6e, 0xb,  0xf3, 0x26,
                        0x9b, 0x7a, 0x34, 0x5f, 0x1f, 0x48, 0x4e, 0x8d,
                        0x3a, 0x3,  0x24, 0xaf, 0xd4, 0x32, 0x3f, 0x8d};
  char hash[32];
  assert_true(transaction_envelope_hash(&transactionEnvelope, hash));
  assert_memory_equal(expect_hash, hash, 32);
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_transaction_envelope_hash),

  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
