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

void test_allow_trust(void **state) {
  struct Operation operation = {
      .source_account_present = false,
      .type = ALLOW_TRUST,
      .allowTrustOp = {
          .trustor = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN",
          .assetCode = "USD",
          .authorize = TRUST_LINE_ENTRY_ALLOW_TRUST_OP_AUTHORIZED_FLAG}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x7,  0x0,  0x0,
                0x0,  0x0,  0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f, 0x36, 0x6f,
                0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                0x24, 0xdf, 0x15, 0xc5, 0x0,  0x0,  0x0,  0x1,  0x55, 0x53,
                0x44, 0x0,  0x0,  0x0,  0x0,  0x1};
  assert_int_equal(buf_size0, 56);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 56);
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

void test_manage_buy_offer(void **state) {
  struct Asset selling = {.type = ASSET_TYPE_NATIVE};
  struct Asset buying = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  int64_t buyAmount = 50000000;
  struct Price price = {.n = 1, .d = 2};
  int64_t offerID = 1234567;

  struct Operation operation = {.source_account_present = false,
                                .type = MANAGE_BUY_OFFER,
                                .manageSellOfferOp = {
                                    .selling = selling,
                                    .buying = buying,
                                    .amount = buyAmount,
                                    .price = price,
                                    .offerID = offerID,
                                }};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xc,  0x0,  0x0,
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

void test_inflation(void **state) {
  struct Operation operation = {
      .source_account_present = false,
      .type = INFLATION,
  };

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9};
  assert_int_equal(buf_size0, 8);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 8);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_manage_data(void **state) {
  struct Operation operation = {.source_account_present = false,
                                .type = MANAGE_DATA,
                                .manageDataOp = {
                                    .dataName = "Hello",
                                    .dataValueLength = 6,
                                    .dataValue = "World",
                                }};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xa,  0x0,
                0x0, 0x0,  0x5,  0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x0,
                0x0, 0x0,  0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,
                0x6, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x0,  0x0,  0x0};
  assert_int_equal(buf_size0, 36);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 36);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_account_merge(void **state) {
  struct MuxedAccount destination = {
      .type = KEY_TYPE_ED25519,
      .ed25519 = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO"};

  struct Operation operation = {.source_account_present = false,
                                .type = ACCOUNT_MERGE,
                                .accountMergeOp = {
                                    .destination = destination,
                                }};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x8,  0x0,
                0x0,  0x0,  0x0,  0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff,
                0x7,  0x57, 0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74,
                0x46, 0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd,
                0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12};
  assert_int_equal(buf_size0, 44);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 44);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_begin_sponsoring_future_reserves(void **state) {

  struct Operation operation = {
      .source_account_present = false,
      .type = BEGIN_SPONSORING_FUTURE_RESERVES,
      .beginSponsoringFutureReservesOp = {
          .sponsoredID =
              "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO",
      }};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x10, 0x0,
                0x0,  0x0,  0x0,  0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff,
                0x7,  0x57, 0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74,
                0x46, 0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd,
                0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12};
  assert_int_equal(buf_size0, 44);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 44);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_end_sponsoring_future_reserves(void **state) {

  struct Operation operation = {
      .source_account_present = false,
      .type = END_SPONSORING_FUTURE_RESERVES,
  };

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x11};
  assert_int_equal(buf_size0, 8);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 8);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_claim_claimable_balance(void **state) {

  struct Operation operation = {
      .source_account_present = false,
      .type = CLAIM_CLAIMABLE_BALANCE,
      .claimClaimableBalanceOp = {.balanceID =
                                      "00000000da0d57da7d4850e7fc10d2a9d0ebc731"
                                      "f7afb40574c03395b17d49149b91f5be"}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xf,  0x0,
                0x0,  0x0,  0x0,  0xda, 0xd,  0x57, 0xda, 0x7d, 0x48,
                0x50, 0xe7, 0xfc, 0x10, 0xd2, 0xa9, 0xd0, 0xeb, 0xc7,
                0x31, 0xf7, 0xaf, 0xb4, 0x5,  0x74, 0xc0, 0x33, 0x95,
                0xb1, 0x7d, 0x49, 0x14, 0x9b, 0x91, 0xf5, 0xbe};
  assert_int_equal(buf_size0, 44);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 44);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_set_trust_line_flags(void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Operation operation = {
      .source_account_present = false,
      .type = SET_TRUST_LINE_FLAGS,
      .setTrustLineFlagsOp = {
          .trustor = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO",
          .asset = asset,
          .clearFlags = 1,
          .setFlags = 4}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x15, 0x0,  0x0,  0x0,  0x0,
      0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57, 0x3b, 0x97, 0x74, 0xcd,
      0x32, 0x2e, 0x74, 0x46, 0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd,
      0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12, 0x0,  0x0,  0x0,  0x1,
      0x55, 0x53, 0x44, 0x43, 0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38,
      0xe,  0xfe, 0x98, 0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
      0x24, 0xdf, 0x15, 0xc5, 0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x4};
  assert_int_equal(buf_size0, 96);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 96);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_clawback_claimable_balance(void **state) {
  struct Operation operation = {
      .source_account_present = false,
      .type = CLAWBACK_CLAIMABLE_BALANCE,
      .clawbackClaimableBalanceOp = {
          .balanceID = "00000000da0d57da7d4850e7fc10d2a9d0ebc731"
                       "f7afb40574c03395b17d49149b91f5be"}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x14, 0x0,
                0x0,  0x0,  0x0,  0xda, 0xd,  0x57, 0xda, 0x7d, 0x48,
                0x50, 0xe7, 0xfc, 0x10, 0xd2, 0xa9, 0xd0, 0xeb, 0xc7,
                0x31, 0xf7, 0xaf, 0xb4, 0x5,  0x74, 0xc0, 0x33, 0x95,
                0xb1, 0x7d, 0x49, 0x14, 0x9b, 0x91, 0xf5, 0xbe};
  assert_int_equal(buf_size0, 44);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 44);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_liquidity_pool_deposit() {
  struct Operation operation = {
      .source_account_present = false,
      .type = LIQUIDITY_POOL_DEPOSIT,
      .liquidityPoolDepositOp = {.liquidityPoolID =
                                     "3441bd8b84f0bab631fe3fb01a0b31b588cb04cdf"
                                     "55cffbd30b79e4286fd8689",
                                 .maxAmountA = 50000000,
                                 .maxAmountB = 10000000,
                                 .minPrice = {.n = 1, .d = 2},
                                 .maxPrice = {.n = 2, .d = 1}}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x16, 0x34, 0x41, 0xbd, 0x8b,
      0x84, 0xf0, 0xba, 0xb6, 0x31, 0xfe, 0x3f, 0xb0, 0x1a, 0xb,  0x31, 0xb5,
      0x88, 0xcb, 0x4,  0xcd, 0xf5, 0x5c, 0xff, 0xbd, 0x30, 0xb7, 0x9e, 0x42,
      0x86, 0xfd, 0x86, 0x89, 0x0,  0x0,  0x0,  0x0,  0x2,  0xfa, 0xf0, 0x80,
      0x0,  0x0,  0x0,  0x0,  0x0,  0x98, 0x96, 0x80, 0x0,  0x0,  0x0,  0x1,
      0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x0,  0x1};
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

void test_liquidity_pool_withdraw() {
  struct Operation operation = {
      .source_account_present = false,
      .type = LIQUIDITY_POOL_WITHDRAW,
      .liquidityPoolWithdrawOp = {
          .liquidityPoolID = "3441bd8b84f0bab631fe3fb01a0b31b588cb04cdf"
                             "55cffbd30b79e4286fd8689",
          .amount = 50000000,
          .minAmountA = 10000000,
          .minAmountB = 20000000,
      }};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x17, 0x34, 0x41,
                0xbd, 0x8b, 0x84, 0xf0, 0xba, 0xb6, 0x31, 0xfe, 0x3f, 0xb0,
                0x1a, 0xb,  0x31, 0xb5, 0x88, 0xcb, 0x4,  0xcd, 0xf5, 0x5c,
                0xff, 0xbd, 0x30, 0xb7, 0x9e, 0x42, 0x86, 0xfd, 0x86, 0x89,
                0x0,  0x0,  0x0,  0x0,  0x2,  0xfa, 0xf0, 0x80, 0x0,  0x0,
                0x0,  0x0,  0x0,  0x98, 0x96, 0x80, 0x0,  0x0,  0x0,  0x0,
                0x1,  0x31, 0x2d, 0x0};
  assert_int_equal(buf_size0, 64);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 64);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_change_trust_asset() {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Operation operation = {
      .source_account_present = false,
      .type = CHANGE_TRUST,
      .changeTrustOp = {.assetType = CHANGE_TRUST_ASSET_TYPE_ASSET,
                        .limit = 10000000,
                        .line = {.asset = asset}}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x6,  0x0,  0x0,
                0x0,  0x1,  0x55, 0x53, 0x44, 0x43, 0x0,  0x0,  0x0,  0x0,
                0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b, 0xa0, 0xa8,
                0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe,
                0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf,
                0x15, 0xc5, 0x0,  0x0,  0x0,  0x0,  0x0,  0x98, 0x96, 0x80};
  assert_int_equal(buf_size0, 60);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 60);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_change_trust_liquidity_pool_asset() {
  struct Asset assetA = {.type = ASSET_TYPE_NATIVE};
  struct Asset assetB = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct LiquidityPoolAsset liquidityPoolAsset = {
      .fee = 30, .assetA = assetA, .assetB = assetB};
  struct Operation operation = {
      .source_account_present = false,
      .type = CHANGE_TRUST,
      .changeTrustOp = {.assetType =
                            CHANGE_TRUST_ASSET_TYPE_LIQUIDITY_POOL_ASSET,
                        .limit = 10000000,
                        .line = {.liquidityPoolAsset = liquidityPoolAsset}}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x6,  0x0,  0x0,
                0x0,  0x3,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                0x0,  0x0,  0x0,  0x1,  0x55, 0x53, 0x44, 0x43, 0x0,  0x0,
                0x0,  0x0,  0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f, 0x36, 0x6f,
                0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                0x24, 0xdf, 0x15, 0xc5, 0x0,  0x0,  0x0,  0x1e, 0x0,  0x0,
                0x0,  0x0,  0x0,  0x98, 0x96, 0x80};
  assert_int_equal(buf_size0, 76);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 76);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_set_options() {
  struct SignerKey signerKey = {
      .signerKeyType = SIGNER_KEY_TYPE_ED25519,
      .signerKey = {.ed25519 = {0x43, 0xd7, 0xb,  0xdc, 0xef, 0x9a, 0x2f,
                                0xfb, 0x57, 0xe6, 0xe5, 0xaf, 0x9a, 0x15,
                                0xae, 0x67, 0x35, 0xc2, 0x95, 0x9a, 0x50,
                                0xff, 0x2b, 0x34, 0xd7, 0x9a, 0xb0, 0x1f,
                                0xe5, 0x9b, 0x45, 0x70}}};
  struct Signer signer = {.key = signerKey, .weight = 1};
  struct Operation operation = {
      .source_account_present = false,
      .type = SET_OPTIONS,
      .setOptionsOp = {
          .inflationDestPresent = true,
          .inflationDest =
              "GDGU5OAPHNPU5UCLE5RDJHG7PXZFQYWKCFOEXSXNMR6KRQRI5T6XXCD7",
          .clearFlagsPresent = true,
          .clearFlags = 8,
          .setFlagsPresent = true,
          .setFlags = 3,
          .masterWeightPresent = true,
          .masterWeight = 0,
          .lowThresholdPresent = true,
          .lowThreshold = 1,
          .medThresholdPresent = true,
          .medThreshold = 2,
          .highThresholdPresent = true,
          .highThreshold = 3,
          .homeDomainPresent = true,
          .homeDomain = "www.example.com",
          .signerPresent = true,
          .signer = signer}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x5,  0x0,  0x0,  0x0,  0x1,
      0x0,  0x0,  0x0,  0x0,  0xcd, 0x4e, 0xb8, 0xf,  0x3b, 0x5f, 0x4e, 0xd0,
      0x4b, 0x27, 0x62, 0x34, 0x9c, 0xdf, 0x7d, 0xf2, 0x58, 0x62, 0xca, 0x11,
      0x5c, 0x4b, 0xca, 0xed, 0x64, 0x7c, 0xa8, 0xc2, 0x28, 0xec, 0xfd, 0x7b,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x8,  0x0,  0x0,  0x0,  0x1,
      0x0,  0x0,  0x0,  0x3,  0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x1,
      0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x3,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0xf,  0x77, 0x77, 0x77, 0x2e,
      0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x0,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x43, 0xd7, 0xb,  0xdc,
      0xef, 0x9a, 0x2f, 0xfb, 0x57, 0xe6, 0xe5, 0xaf, 0x9a, 0x15, 0xae, 0x67,
      0x35, 0xc2, 0x95, 0x9a, 0x50, 0xff, 0x2b, 0x34, 0xd7, 0x9a, 0xb0, 0x1f,
      0xe5, 0x9b, 0x45, 0x70, 0x0,  0x0,  0x0,  0x1};
  assert_int_equal(buf_size0, 164);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 164);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_set_options_empty() {

  struct Operation operation = {
      .source_account_present = false, .type = SET_OPTIONS, .setOptionsOp = {}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5, 0x0, 0x0, 0x0,
                0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
                0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
                0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  assert_int_equal(buf_size0, 44);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 44);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_clawback() {
  struct MuxedAccount fromAccount = {
      .type = KEY_TYPE_ED25519,
      .ed25519 = "GDGU5OAPHNPU5UCLE5RDJHG7PXZFQYWKCFOEXSXNMR6KRQRI5T6XXCD7"};
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Operation operation = {
      .source_account_present = false,
      .type = CLAWBACK,
      .clawbackOp = {.asset = asset, .from = fromAccount, .amount = 50000000}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x13, 0x0,  0x0,  0x0,  0x1,
      0x55, 0x53, 0x44, 0x43, 0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38,
      0xe,  0xfe, 0x98, 0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
      0x24, 0xdf, 0x15, 0xc5, 0x0,  0x0,  0x0,  0x0,  0xcd, 0x4e, 0xb8, 0xf,
      0x3b, 0x5f, 0x4e, 0xd0, 0x4b, 0x27, 0x62, 0x34, 0x9c, 0xdf, 0x7d, 0xf2,
      0x58, 0x62, 0xca, 0x11, 0x5c, 0x4b, 0xca, 0xed, 0x64, 0x7c, 0xa8, 0xc2,
      0x28, 0xec, 0xfd, 0x7b, 0x0,  0x0,  0x0,  0x0,  0x2,  0xfa, 0xf0, 0x80};
  assert_int_equal(buf_size0, 96);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 96);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_revoke_sponsorship_account() {
  struct Operation operation = {
      .source_account_present = false,
      .type = REVOKE_SPONSORSHIP,
      .revokeSponsorshipOp = {
          .revokeSponsorshipType = REVOKE_SPONSORSHIP_TYPE_ACCOUNT,
          .sponsorship = {
              .accountID =
                  "GDGU5OAPHNPU5UCLE5RDJHG7PXZFQYWKCFOEXSXNMR6KRQRI5T6XXCD7"}}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x12, 0x0,
                0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                0x0,  0x0,  0xcd, 0x4e, 0xb8, 0xf,  0x3b, 0x5f, 0x4e,
                0xd0, 0x4b, 0x27, 0x62, 0x34, 0x9c, 0xdf, 0x7d, 0xf2,
                0x58, 0x62, 0xca, 0x11, 0x5c, 0x4b, 0xca, 0xed, 0x64,
                0x7c, 0xa8, 0xc2, 0x28, 0xec, 0xfd, 0x7b};
  assert_int_equal(buf_size0, 52);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 52);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_revoke_sponsorship_asset_asset() {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct RevokeSponsorshipTrustLine revokeSponsorshipTrustLine = {
      .type = REVOKE_SPONSORSHIP_TRUST_LINE_TYPE_ASSET,
      .accountID = "GDGU5OAPHNPU5UCLE5RDJHG7PXZFQYWKCFOEXSXNMR6KRQRI5T6XXCD7",

      .trustLine = {.asset = asset}};
  struct Operation operation = {
      .source_account_present = false,
      .type = REVOKE_SPONSORSHIP,
      .revokeSponsorshipOp = {
          .revokeSponsorshipType = REVOKE_SPONSORSHIP_TYPE_TRUSTLINE,
          .sponsorship = {.trustLine = revokeSponsorshipTrustLine}}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x12, 0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0xcd, 0x4e, 0xb8, 0xf,
      0x3b, 0x5f, 0x4e, 0xd0, 0x4b, 0x27, 0x62, 0x34, 0x9c, 0xdf, 0x7d, 0xf2,
      0x58, 0x62, 0xca, 0x11, 0x5c, 0x4b, 0xca, 0xed, 0x64, 0x7c, 0xa8, 0xc2,
      0x28, 0xec, 0xfd, 0x7b, 0x0,  0x0,  0x0,  0x1,  0x55, 0x53, 0x44, 0x43,
      0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe,
      0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5};
  assert_int_equal(buf_size0, 96);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 96);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_revoke_sponsorship_asset_liquidity_pool_id() {
  struct RevokeSponsorshipTrustLine revokeSponsorshipTrustLine = {
      .type = REVOKE_SPONSORSHIP_TRUST_LINE_TYPE_LIQUIDITY_POOL_ID,
      .accountID = "GDGU5OAPHNPU5UCLE5RDJHG7PXZFQYWKCFOEXSXNMR6KRQRI5T6XXCD7",
      .trustLine = {.liquidityPoolId = "3441bd8b84f0bab631fe3fb01a0b31b588cb04c"
                                       "df55cffbd30b79e4286fd8689"}};
  struct Operation operation = {
      .source_account_present = false,
      .type = REVOKE_SPONSORSHIP,
      .revokeSponsorshipOp = {
          .revokeSponsorshipType = REVOKE_SPONSORSHIP_TYPE_TRUSTLINE,
          .sponsorship = {.trustLine = revokeSponsorshipTrustLine}}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x12, 0x0,  0x0,
                0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,
                0xcd, 0x4e, 0xb8, 0xf,  0x3b, 0x5f, 0x4e, 0xd0, 0x4b, 0x27,
                0x62, 0x34, 0x9c, 0xdf, 0x7d, 0xf2, 0x58, 0x62, 0xca, 0x11,
                0x5c, 0x4b, 0xca, 0xed, 0x64, 0x7c, 0xa8, 0xc2, 0x28, 0xec,
                0xfd, 0x7b, 0x0,  0x0,  0x0,  0x3,  0x34, 0x41, 0xbd, 0x8b,
                0x84, 0xf0, 0xba, 0xb6, 0x31, 0xfe, 0x3f, 0xb0, 0x1a, 0xb,
                0x31, 0xb5, 0x88, 0xcb, 0x4,  0xcd, 0xf5, 0x5c, 0xff, 0xbd,
                0x30, 0xb7, 0x9e, 0x42, 0x86, 0xfd, 0x86, 0x89};
  assert_int_equal(buf_size0, 88);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 88);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_revoke_sponsorship_offer() {
  struct Operation operation = {
      .source_account_present = false,
      .type = REVOKE_SPONSORSHIP,
      .revokeSponsorshipOp = {
          .revokeSponsorshipType = REVOKE_SPONSORSHIP_TYPE_OFFER,
          .sponsorship = {.offer = {.sellerID = "GDGU5OAPHNPU5UCLE5RDJHG7PXZFQY"
                                                "WKCFOEXSXNMR6KRQRI5T6XXCD7",
                                    .offerID = 12345}}}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x12, 0x0,  0x0,
                0x0,  0x0,  0x0,  0x0,  0x0,  0x2,  0x0,  0x0,  0x0,  0x0,
                0xcd, 0x4e, 0xb8, 0xf,  0x3b, 0x5f, 0x4e, 0xd0, 0x4b, 0x27,
                0x62, 0x34, 0x9c, 0xdf, 0x7d, 0xf2, 0x58, 0x62, 0xca, 0x11,
                0x5c, 0x4b, 0xca, 0xed, 0x64, 0x7c, 0xa8, 0xc2, 0x28, 0xec,
                0xfd, 0x7b, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x30, 0x39};
  assert_int_equal(buf_size0, 60);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 60);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_revoke_sponsorship_data() {
  struct Operation operation = {
      .source_account_present = false,
      .type = REVOKE_SPONSORSHIP,
      .revokeSponsorshipOp = {
          .revokeSponsorshipType = REVOKE_SPONSORSHIP_TYPE_DATA,
          .sponsorship = {.data = {.accountID = "GDGU5OAPHNPU5UCLE5RDJHG7PXZFQY"
                                                "WKCFOEXSXNMR6KRQRI5T6XXCD7",
                                   .dataName = "c stellar base"}}}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x12, 0x0,  0x0,  0x0,  0x0,
      0x0,  0x0,  0x0,  0x3,  0x0,  0x0,  0x0,  0x0,  0xcd, 0x4e, 0xb8, 0xf,
      0x3b, 0x5f, 0x4e, 0xd0, 0x4b, 0x27, 0x62, 0x34, 0x9c, 0xdf, 0x7d, 0xf2,
      0x58, 0x62, 0xca, 0x11, 0x5c, 0x4b, 0xca, 0xed, 0x64, 0x7c, 0xa8, 0xc2,
      0x28, 0xec, 0xfd, 0x7b, 0x0,  0x0,  0x0,  0xe,  0x63, 0x20, 0x73, 0x74,
      0x65, 0x6c, 0x6c, 0x61, 0x72, 0x20, 0x62, 0x61, 0x73, 0x65, 0x0,  0x0};
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

void test_revoke_sponsorship_claimable_balance() {
  struct Operation operation = {
      .source_account_present = false,
      .type = REVOKE_SPONSORSHIP,
      .revokeSponsorshipOp = {
          .revokeSponsorshipType = REVOKE_SPONSORSHIP_TYPE_CLAIMABLE_BALANCE,
          .sponsorship = {.claimableBalanceID =
                              "00000000da0d57da7d4850e7fc10d2a9d0ebc731f7afb405"
                              "74c03395b17d49149b91f5be"}}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x12, 0x0,
                0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x4,  0x0,  0x0,
                0x0,  0x0,  0xda, 0xd,  0x57, 0xda, 0x7d, 0x48, 0x50,
                0xe7, 0xfc, 0x10, 0xd2, 0xa9, 0xd0, 0xeb, 0xc7, 0x31,
                0xf7, 0xaf, 0xb4, 0x5,  0x74, 0xc0, 0x33, 0x95, 0xb1,
                0x7d, 0x49, 0x14, 0x9b, 0x91, 0xf5, 0xbe};
  assert_int_equal(buf_size0, 52);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 52);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_revoke_sponsorship_signer() {
  struct SignerKey signerKey = {
      .signerKeyType = SIGNER_KEY_TYPE_ED25519,
      .signerKey = {.ed25519 = {0xcd, 0x4e, 0xb8, 0xf,  0x3b, 0x5f, 0x4e,
                                0xd0, 0x4b, 0x27, 0x62, 0x34, 0x9c, 0xdf,
                                0x7d, 0xf2, 0x58, 0x62, 0xca, 0x11, 0x5c,
                                0x4b, 0xca, 0xed, 0x64, 0x7c, 0xa8, 0xc2,
                                0x28, 0xec, 0xfd, 0x7b}}};
  struct Operation operation = {
      .source_account_present = false,
      .type = REVOKE_SPONSORSHIP,
      .revokeSponsorshipOp = {
          .revokeSponsorshipType = REVOKE_SPONSORSHIP_TYPE_SIGNER,
          .sponsorship = {
              .signer = {.accountID = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IH"
                                      "OJAPP5RE34K4KZVN",
                         .signerKey = signerKey}}}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {
      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x12, 0x0,  0x0,  0x0,  0x1,
      0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe,
      0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5,
      0x0,  0x0,  0x0,  0x0,  0xcd, 0x4e, 0xb8, 0xf,  0x3b, 0x5f, 0x4e, 0xd0,
      0x4b, 0x27, 0x62, 0x34, 0x9c, 0xdf, 0x7d, 0xf2, 0x58, 0x62, 0xca, 0x11,
      0x5c, 0x4b, 0xca, 0xed, 0x64, 0x7c, 0xa8, 0xc2, 0x28, 0xec, 0xfd, 0x7b};
  assert_int_equal(buf_size0, 84);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 84);
  assert_memory_equal(buf1, xdr, buf_size1);
}

void test_revoke_sponsorship_liquidity_pool() {
  struct Operation operation = {
      .source_account_present = false,
      .type = REVOKE_SPONSORSHIP,
      .revokeSponsorshipOp = {
          .revokeSponsorshipType = REVOKE_SPONSORSHIP_TYPE_LIQUIDITY_POOL,
          .sponsorship = {.liquidityPoolID =
                              "3441bd8b84f0bab631fe3fb01a0b31b588cb04cdf55cffbd"
                              "30b79e4286fd8689"}}};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(operation_to_xdr(&operation, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x12, 0x0,  0x0,
                0x0,  0x0,  0x0,  0x0,  0x0,  0x5,  0x34, 0x41, 0xbd, 0x8b,
                0x84, 0xf0, 0xba, 0xb6, 0x31, 0xfe, 0x3f, 0xb0, 0x1a, 0xb,
                0x31, 0xb5, 0x88, 0xcb, 0x4,  0xcd, 0xf5, 0x5c, 0xff, 0xbd,
                0x30, 0xb7, 0x9e, 0x42, 0x86, 0xfd, 0x86, 0x89};
  assert_int_equal(buf_size0, 48);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_Operation to;
  assert_true(operation_to_xdr_object(&operation, &to));
  struct Operation from;
  assert_true(operation_from_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(operation_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 48);
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
      cmocka_unit_test(test_allow_trust),
      cmocka_unit_test(test_bump_sequence),
      cmocka_unit_test(test_manage_buy_offer),
      cmocka_unit_test(test_path_payment_strict_send),
      cmocka_unit_test(test_inflation),
      cmocka_unit_test(test_manage_data),
      cmocka_unit_test(test_account_merge),
      cmocka_unit_test(test_begin_sponsoring_future_reserves),
      cmocka_unit_test(test_end_sponsoring_future_reserves),
      cmocka_unit_test(test_claim_claimable_balance),
      cmocka_unit_test(test_set_trust_line_flags),
      cmocka_unit_test(test_clawback_claimable_balance),
      cmocka_unit_test(test_liquidity_pool_deposit),
      cmocka_unit_test(test_liquidity_pool_withdraw),
      cmocka_unit_test(test_change_trust_asset),
      cmocka_unit_test(test_change_trust_liquidity_pool_asset),
      cmocka_unit_test(test_set_options),
      cmocka_unit_test(test_set_options_empty),
      cmocka_unit_test(test_clawback),
      cmocka_unit_test(test_revoke_sponsorship_account),
      cmocka_unit_test(test_revoke_sponsorship_asset_asset),
      cmocka_unit_test(test_revoke_sponsorship_asset_liquidity_pool_id),
      cmocka_unit_test(test_revoke_sponsorship_offer),
      cmocka_unit_test(test_revoke_sponsorship_data),
      cmocka_unit_test(test_revoke_sponsorship_claimable_balance),
      cmocka_unit_test(test_revoke_sponsorship_signer),
      cmocka_unit_test(test_revoke_sponsorship_liquidity_pool),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
