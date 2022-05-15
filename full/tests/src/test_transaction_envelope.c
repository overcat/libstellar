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

void test_transaction_envelope_sign_with_one_signer(void **state) {
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

  char *seed0 = "SAAPEEEUH2XAWOTAQ2VTSAFBEOZNJBYI63P2T5QRMLG2PTSB6THHUZXS";
  struct Keypair signer0;
  assert_true(keypair_from_secret(&signer0, seed0));
  assert_true(transaction_envelope_sign(&signer0, &transactionEnvelope));
  assert_int_equal(transactionEnvelope.signatures_len, 1);
  struct DecoratedSignature expectDecoratedSignature0 = {
      .signatureHint = {0xff, 0xf8, 0xc9, 0x53},
      .signature = {0xab, 0xc7, 0xa6, 0x38, 0x6c, 0xf9, 0xcd, 0xf,  0x62, 0x2,
                    0x85, 0x7a, 0xbc, 0x65, 0x8f, 0x61, 0xb5, 0xc4, 0x59, 0xfa,
                    0xa5, 0xe5, 0xc6, 0x69, 0x65, 0xca, 0xb0, 0x61, 0xc5, 0x25,
                    0xd1, 0xdf, 0xcd, 0x71, 0x6c, 0x25, 0x57, 0xa0, 0x85, 0xf0,
                    0xd,  0x14, 0x39, 0x18, 0x99, 0x6f, 0x48, 0x51, 0x3b, 0xff,
                    0x50, 0xbd, 0x3,  0x20, 0xd0, 0xa3, 0x28, 0xfc, 0xda, 0xe8,
                    0xf8, 0x5,  0xa0, 0x0}};

  assert_memory_equal(&expectDecoratedSignature0,
                      transactionEnvelope.signatures,
                      sizeof(struct DecoratedSignature));
}

void test_transaction_envelope_sign_with_two_signers(void **state) {
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

  char *seed0 = "SAAPEEEUH2XAWOTAQ2VTSAFBEOZNJBYI63P2T5QRMLG2PTSB6THHUZXS";
  struct Keypair signer0;
  assert_true(keypair_from_secret(&signer0, seed0));
  assert_true(transaction_envelope_sign(&signer0, &transactionEnvelope));
  assert_int_equal(transactionEnvelope.signatures_len, 1);
  struct DecoratedSignature expectDecoratedSignature0 = {
      .signatureHint = {0xff, 0xf8, 0xc9, 0x53},
      .signature = {0xab, 0xc7, 0xa6, 0x38, 0x6c, 0xf9, 0xcd, 0xf,  0x62, 0x2,
                    0x85, 0x7a, 0xbc, 0x65, 0x8f, 0x61, 0xb5, 0xc4, 0x59, 0xfa,
                    0xa5, 0xe5, 0xc6, 0x69, 0x65, 0xca, 0xb0, 0x61, 0xc5, 0x25,
                    0xd1, 0xdf, 0xcd, 0x71, 0x6c, 0x25, 0x57, 0xa0, 0x85, 0xf0,
                    0xd,  0x14, 0x39, 0x18, 0x99, 0x6f, 0x48, 0x51, 0x3b, 0xff,
                    0x50, 0xbd, 0x3,  0x20, 0xd0, 0xa3, 0x28, 0xfc, 0xda, 0xe8,
                    0xf8, 0x5,  0xa0, 0x0}};

  char *seed1 = "SDVSRLOZVE6IMHT26LWTZUJ2PRGYCOU6IQBCHFT6JVGITBJK3FHLQ5UD";
  struct Keypair signer1;
  assert_true(keypair_from_secret(&signer1, seed1));
  assert_true(transaction_envelope_sign(&signer1, &transactionEnvelope));
  assert_int_equal(transactionEnvelope.signatures_len, 2);
  struct DecoratedSignature expectDecoratedSignature1 = {
      .signatureHint = {0x4b, 0xa5, 0xee, 0x84},
      .signature = {0x40, 0xce, 0x2,  0x3d, 0x4f, 0x2e, 0x9d, 0x4b, 0x2a, 0x70,
                    0xf3, 0xa2, 0xd5, 0xd4, 0x19, 0x99, 0xb7, 0x61, 0xe8, 0xf0,
                    0x9,  0x33, 0xfc, 0x56, 0xd8, 0xa8, 0xce, 0x63, 0xb9, 0x7a,
                    0xaa, 0x5,  0xe6, 0x17, 0x7a, 0xdc, 0x29, 0x67, 0x53, 0x23,
                    0x1d, 0x64, 0xbc, 0x0,  0xb5, 0xb2, 0xa0, 0x8,  0x67, 0xae,
                    0x4b, 0x7c, 0x7,  0x1e, 0x1d, 0x1e, 0x1a, 0x8,  0xc9, 0x6f,
                    0xc6, 0x20, 0x8f, 0x5}};
  assert_memory_equal(&expectDecoratedSignature0,
                      transactionEnvelope.signatures,
                      sizeof(struct DecoratedSignature));

  assert_memory_equal(&expectDecoratedSignature1,
                      transactionEnvelope.signatures + 1,
                      sizeof(struct DecoratedSignature));
}

bool _transaction_envelope_to_xdr(const struct TransactionEnvelope *in,
                                  char **buf, size_t *buf_size) {
  stellarxdr_TransactionEnvelope transactionEnvelope_xdr;
  if (!transaction_envelope_to_xdr_object(in, &transactionEnvelope_xdr)) {
    return false;
  }
  FILE *fp = open_memstream(buf, buf_size);
  XDR xdr;
  xdrstdio_create(&xdr, fp, XDR_ENCODE);
  if (!xdr_stellarxdr_TransactionEnvelope(&xdr, &transactionEnvelope_xdr)) {
    fclose(fp);
    return false;
  }
  fclose(fp);
  return true;
}

void test_transaction_envelope_to_xdr_object(void **state) {
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

  char *seed0 = "SAAPEEEUH2XAWOTAQ2VTSAFBEOZNJBYI63P2T5QRMLG2PTSB6THHUZXS";
  struct Keypair signer0;
  assert_true(keypair_from_secret(&signer0, seed0));
  assert_true(transaction_envelope_sign(&signer0, &transactionEnvelope));
  char *seed1 = "SDVSRLOZVE6IMHT26LWTZUJ2PRGYCOU6IQBCHFT6JVGITBJK3FHLQ5UD";
  struct Keypair signer1;
  assert_true(keypair_from_secret(&signer1, seed1));
  assert_true(transaction_envelope_sign(&signer1, &transactionEnvelope));

  char expectXdr[] = {
      0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x0,  0x0,  0x7f, 0xff, 0xb1, 0x32,
      0x3a, 0xff, 0x7,  0x57, 0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46,
      0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd, 0xfc, 0x74, 0xdb, 0x7d,
      0x6e, 0x1d, 0x9d, 0x12, 0x0,  0x0,  0x0,  0x64, 0x0,  0x0,  0x0,  0x0,
      0x49, 0x96, 0x2,  0xd2, 0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x61, 0x53, 0xd8, 0x7b,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0xf,  0x48, 0x65, 0x6c, 0x6c,
      0x6f, 0x2c, 0x20, 0x53, 0x74, 0x65, 0x6c, 0x6c, 0x61, 0x72, 0x21, 0x0,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xb,
      0x0,  0x0,  0x0,  0x0,  0x49, 0x96, 0x2,  0xd2, 0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x2,  0xff, 0xf8, 0xc9, 0x53, 0x0,  0x0,  0x0,  0x40,
      0xab, 0xc7, 0xa6, 0x38, 0x6c, 0xf9, 0xcd, 0xf,  0x62, 0x2,  0x85, 0x7a,
      0xbc, 0x65, 0x8f, 0x61, 0xb5, 0xc4, 0x59, 0xfa, 0xa5, 0xe5, 0xc6, 0x69,
      0x65, 0xca, 0xb0, 0x61, 0xc5, 0x25, 0xd1, 0xdf, 0xcd, 0x71, 0x6c, 0x25,
      0x57, 0xa0, 0x85, 0xf0, 0xd,  0x14, 0x39, 0x18, 0x99, 0x6f, 0x48, 0x51,
      0x3b, 0xff, 0x50, 0xbd, 0x3,  0x20, 0xd0, 0xa3, 0x28, 0xfc, 0xda, 0xe8,
      0xf8, 0x5,  0xa0, 0x0,  0x4b, 0xa5, 0xee, 0x84, 0x0,  0x0,  0x0,  0x40,
      0x40, 0xce, 0x2,  0x3d, 0x4f, 0x2e, 0x9d, 0x4b, 0x2a, 0x70, 0xf3, 0xa2,
      0xd5, 0xd4, 0x19, 0x99, 0xb7, 0x61, 0xe8, 0xf0, 0x9,  0x33, 0xfc, 0x56,
      0xd8, 0xa8, 0xce, 0x63, 0xb9, 0x7a, 0xaa, 0x5,  0xe6, 0x17, 0x7a, 0xdc,
      0x29, 0x67, 0x53, 0x23, 0x1d, 0x64, 0xbc, 0x0,  0xb5, 0xb2, 0xa0, 0x8,
      0x67, 0xae, 0x4b, 0x7c, 0x7,  0x1e, 0x1d, 0x1e, 0x1a, 0x8,  0xc9, 0x6f,
      0xc6, 0x20, 0x8f, 0x5};
  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(
      _transaction_envelope_to_xdr(&transactionEnvelope, &buf, &buf_size));
  assert_int_equal(268, buf_size);
  assert_memory_equal(buf, expectXdr, 268);
}

bool _transaction_envelope_from_xdr(char *buf, size_t buf_size,
                                    struct TransactionEnvelope *out) {
  FILE *fp = fmemopen(buf, buf_size, "r");
  XDR xdr;
  stellarxdr_TransactionEnvelope *transactionEnvelope_xdr =
      malloc(sizeof(stellarxdr_TransactionEnvelope));
  if (transactionEnvelope_xdr == NULL) {
    return false;
  }
  xdrstdio_create(&xdr, fp, XDR_DECODE);
  if (!xdr_stellarxdr_TransactionEnvelope(&xdr, transactionEnvelope_xdr)) {
    fclose(fp);
    return false;
  }
  if (!transaction_envelope_from_xdr_object(transactionEnvelope_xdr, out,
                                            PUBLIC_NETWORK_PASSPHRASE)) {
    return false;
  }
  fclose(fp);
  return true;
}

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

void test_transaction_envelope_from_xdr_object(void **state) {
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

  char *seed0 = "SAAPEEEUH2XAWOTAQ2VTSAFBEOZNJBYI63P2T5QRMLG2PTSB6THHUZXS";
  struct Keypair signer0;
  assert_true(keypair_from_secret(&signer0, seed0));
  assert_true(transaction_envelope_sign(&signer0, &transactionEnvelope));
  char *seed1 = "SDVSRLOZVE6IMHT26LWTZUJ2PRGYCOU6IQBCHFT6JVGITBJK3FHLQ5UD";
  struct Keypair signer1;
  assert_true(keypair_from_secret(&signer1, seed1));
  assert_true(transaction_envelope_sign(&signer1, &transactionEnvelope));

  char xdr[] = {
      0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x0,  0x0,  0x7f, 0xff, 0xb1, 0x32,
      0x3a, 0xff, 0x7,  0x57, 0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46,
      0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd, 0xfc, 0x74, 0xdb, 0x7d,
      0x6e, 0x1d, 0x9d, 0x12, 0x0,  0x0,  0x0,  0x64, 0x0,  0x0,  0x0,  0x0,
      0x49, 0x96, 0x2,  0xd2, 0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x61, 0x53, 0xd8, 0x7b,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0xf,  0x48, 0x65, 0x6c, 0x6c,
      0x6f, 0x2c, 0x20, 0x53, 0x74, 0x65, 0x6c, 0x6c, 0x61, 0x72, 0x21, 0x0,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xb,
      0x0,  0x0,  0x0,  0x0,  0x49, 0x96, 0x2,  0xd2, 0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x2,  0xff, 0xf8, 0xc9, 0x53, 0x0,  0x0,  0x0,  0x40,
      0xab, 0xc7, 0xa6, 0x38, 0x6c, 0xf9, 0xcd, 0xf,  0x62, 0x2,  0x85, 0x7a,
      0xbc, 0x65, 0x8f, 0x61, 0xb5, 0xc4, 0x59, 0xfa, 0xa5, 0xe5, 0xc6, 0x69,
      0x65, 0xca, 0xb0, 0x61, 0xc5, 0x25, 0xd1, 0xdf, 0xcd, 0x71, 0x6c, 0x25,
      0x57, 0xa0, 0x85, 0xf0, 0xd,  0x14, 0x39, 0x18, 0x99, 0x6f, 0x48, 0x51,
      0x3b, 0xff, 0x50, 0xbd, 0x3,  0x20, 0xd0, 0xa3, 0x28, 0xfc, 0xda, 0xe8,
      0xf8, 0x5,  0xa0, 0x0,  0x4b, 0xa5, 0xee, 0x84, 0x0,  0x0,  0x0,  0x40,
      0x40, 0xce, 0x2,  0x3d, 0x4f, 0x2e, 0x9d, 0x4b, 0x2a, 0x70, 0xf3, 0xa2,
      0xd5, 0xd4, 0x19, 0x99, 0xb7, 0x61, 0xe8, 0xf0, 0x9,  0x33, 0xfc, 0x56,
      0xd8, 0xa8, 0xce, 0x63, 0xb9, 0x7a, 0xaa, 0x5,  0xe6, 0x17, 0x7a, 0xdc,
      0x29, 0x67, 0x53, 0x23, 0x1d, 0x64, 0xbc, 0x0,  0xb5, 0xb2, 0xa0, 0x8,
      0x67, 0xae, 0x4b, 0x7c, 0x7,  0x1e, 0x1d, 0x1e, 0x1a, 0x8,  0xc9, 0x6f,
      0xc6, 0x20, 0x8f, 0x5};

  struct TransactionEnvelope out;
  assert_true(_transaction_envelope_from_xdr(xdr, sizeof(xdr), &out));

  // TODO: recheck here
  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(_transaction_envelope_to_xdr(&out, &buf, &buf_size));
  assert_int_equal(268, buf_size);
  assert_memory_equal(buf, xdr, 268);
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_transaction_envelope_hash),
      cmocka_unit_test(test_transaction_envelope_sign_with_one_signer),
      cmocka_unit_test(test_transaction_envelope_sign_with_two_signers),
      cmocka_unit_test(test_transaction_envelope_to_xdr_object),
      cmocka_unit_test(test_transaction_envelope_from_xdr_object),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
