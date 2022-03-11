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

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  assert_false(from.source_account_present);
  assert_int_equal(from.type, PAYMENT);
  assert_int_equal(from.paymentOp.amount, 10000000);
  assert_int_equal(from.paymentOp.asset.type, asset.type);
  assert_string_equal(from.paymentOp.destination, destination);
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

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  assert_false(from.source_account_present);
  assert_int_equal(from.type, PAYMENT);
  assert_int_equal(from.paymentOp.amount, 10000000);
  assert_int_equal(from.paymentOp.asset.type, asset.type);
  assert_string_equal(from.paymentOp.destination, destination);
}

void test_path_payment_strict_receive(void **state) {
  struct MuxedAccount destination = {
      .type = KEY_TYPE_ED25519,
      .ed25519 = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO"};
  struct Asset destAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset sendAsset = {.type = ASSET_TYPE_NATIVE};
  int64_t destAmount = 10000000;
  int64_t sendMax = 50000000;
  uint8_t pathLen = 2;
  struct Operation operation = {.source_account_present = false,
                                .type = PATH_PAYMENT_STRICT_RECEIVE,
                                .pathPaymentStrictReceiveOp = {
                                    .destination = destination,
                                    .sendAsset = sendAsset,
                                    .destAsset = destAsset,
                                    .destAmount = destAmount,
                                    .sendMax = sendMax,
                                    .pathLen = pathLen,
                                }};
  struct Asset asset0 = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset1 = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDABC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  operation.pathPaymentStrictReceiveOp.path[0] = asset0;
  operation.pathPaymentStrictReceiveOp.path[1] = asset1;

  char *buf = NULL;
  size_t buf_size = 0;
  assert_true(operation_to_xdr(&operation, &buf, &buf_size));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x0,  0x2,  0xfa, 0xf0, 0x80, 0x0,  0x0,  0x0,  0x0,
      0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57, 0x3b, 0x97, 0x74, 0xcd,
      0x32, 0x2e, 0x74, 0x46, 0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd,
      0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12, 0x0,  0x0,  0x0,  0x1,
      0x55, 0x53, 0x44, 0x43, 0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38,
      0xe,  0xfe, 0x98, 0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
      0x24, 0xdf, 0x15, 0xc5, 0x0,  0x0,  0x0,  0x0,  0x0,  0x98, 0x96, 0x80,
      0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x0,  0x1,  0x55, 0x53, 0x44, 0x0,
      0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe,
      0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5,
      0x0,  0x0,  0x0,  0x2,  0x55, 0x53, 0x44, 0x41, 0x42, 0x43, 0x0,  0x0,
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38,
      0xe,  0xfe, 0x98, 0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
      0x24, 0xdf, 0x15, 0xc5};
  assert_int_equal(buf_size, 208);
  assert_memory_equal(buf, xdr, buf_size);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 208);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_manage_sell_offer(void **state) {
  struct Asset selling = {.type = ASSET_TYPE_NATIVE};
  struct Asset buying = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  int64_t amount = 50000000;
  struct Price price = {.n = 1, .d = 2};
  int64_t offerID = 1234567;

  struct Operation operation = {.source_account_present = false,
                                .type = MANAGE_SELL_OFFER,
                                .manageSellOfferOp = {
                                    .selling = selling,
                                    .buying = buying,
                                    .amount = amount,
                                    .price = price,
                                    .offerID = offerID,
                                }};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x3,  0x0,  0x0,
                0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x55, 0x53, 0x44, 0x43,
                0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe,
                0x98, 0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,  0x72, 0x40,
                0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5, 0x0,  0x0,  0x0,  0x0,
                0x2,  0xfa, 0xf0, 0x80, 0x0,  0x0,  0x0,  0x1,  0x0,  0x0,
                0x0,  0x2,  0x0,  0x0,  0x0,  0x0,  0x0,  0x12, 0xd6, 0x87};
  assert_int_equal(buf_size0, 80);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 80);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_create_passive_sell_sell_offer(void **state) {
  struct Asset selling = {.type = ASSET_TYPE_NATIVE};
  struct Asset buying = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  int64_t amount = 50000000;
  struct Price price = {.n = 1, .d = 2};
  int64_t offerID = 1234567;

  struct Operation operation = {.source_account_present = false,
                                .type = CREATE_PASSIVE_SELL_OFFER,
                                .manageSellOfferOp = {
                                    .selling = selling,
                                    .buying = buying,
                                    .amount = amount,
                                    .price = price,
                                    .offerID = offerID,
                                }};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x4,  0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x1,  0x55, 0x53, 0x44, 0x43, 0x0,  0x0,  0x0,  0x0,
      0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b, 0xa0, 0xa8, 0x90, 0xe,
      0xb1, 0xcf, 0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5, 0x0,  0x0,  0x0,  0x0,
      0x2,  0xfa, 0xf0, 0x80, 0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x2};
  assert_int_equal(buf_size0, 72);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 72);
  assert_memory_equal(buf1, xdr, buf_size1);
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

void test_path_payment_strict_send(void **state) {
  struct MuxedAccount destination = {
      .type = KEY_TYPE_ED25519,
      .ed25519 = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO"};
  struct Asset destAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset sendAsset = {.type = ASSET_TYPE_NATIVE};
  int64_t destMin = 10000000;
  int64_t sendAmount = 50000000;
  uint8_t pathLen = 2;
  struct Operation operation = {.source_account_present = false,
                                .type = PATH_PAYMENT_STRICT_SEND,
                                .pathPaymentStrictSendOp = {
                                    .destination = destination,
                                    .sendAsset = sendAsset,
                                    .destAsset = destAsset,
                                    .destMin = destMin,
                                    .sendAmount = sendAmount,
                                    .pathLen = pathLen,
                                }};
  struct Asset asset0 = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset1 = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDABC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  operation.pathPaymentStrictSendOp.path[0] = asset0;
  operation.pathPaymentStrictSendOp.path[1] = asset1;

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xd,  0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x0,  0x2,  0xfa, 0xf0, 0x80, 0x0,  0x0,  0x0,  0x0,
      0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57, 0x3b, 0x97, 0x74, 0xcd,
      0x32, 0x2e, 0x74, 0x46, 0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd,
      0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12, 0x0,  0x0,  0x0,  0x1,
      0x55, 0x53, 0x44, 0x43, 0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38,
      0xe,  0xfe, 0x98, 0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
      0x24, 0xdf, 0x15, 0xc5, 0x0,  0x0,  0x0,  0x0,  0x0,  0x98, 0x96, 0x80,
      0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x0,  0x1,  0x55, 0x53, 0x44, 0x0,
      0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe,
      0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5,
      0x0,  0x0,  0x0,  0x2,  0x55, 0x53, 0x44, 0x41, 0x42, 0x43, 0x0,  0x0,
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38,
      0xe,  0xfe, 0x98, 0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
      0x24, 0xdf, 0x15, 0xc5};
  assert_int_equal(buf_size0, 208);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 208);
  assert_memory_equal(buf1, xdr, buf_size1);
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_create_account),
      cmocka_unit_test(test_payment),
      cmocka_unit_test(test_payment_with_muxed_account),
      cmocka_unit_test(test_path_payment_strict_receive),
      cmocka_unit_test(test_manage_sell_offer),
      cmocka_unit_test(test_create_passive_sell_sell_offer),
      cmocka_unit_test(test_bump_sequence),
      cmocka_unit_test(test_path_payment_strict_send),

  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
