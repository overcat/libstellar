#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/muxed_account.h"
#include <cmocka.h>

void test_muxed_account_from_address_ed25519_account(void **state) {
  char *in = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO";
  struct MuxedAccount out;
  assert_true(muxed_account_from_address(in, &out));
  assert_int_equal(out.type, KEY_TYPE_ED25519);
  assert_string_equal(out.ed25519, in);
}

void test_muxed_account_from_address_muxed_account(void **state) {
  char *in =
      "MB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWOREAAAAAAAAAAE2K4YI";
  struct MuxedAccount out;
  assert_true(muxed_account_from_address(in, &out));
  assert_int_equal(out.type, KEY_TYPE_MUXED_ED25519);
  assert_string_equal(
      out.med25519.ed25519,
      "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO");
  assert_int_equal(out.med25519.id, 1234);
}

void test_muxed_account_to_address_ed25519_account(void **state) {
  struct MuxedAccount in = {
      .type = KEY_TYPE_ED25519,
      .ed25519 = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO"};
  char out[ED25519_PUBLIC_KEY_LENGTH + 1];
  assert_true(muxed_account_to_address(&in, out));
  assert_string_equal(
      out, "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO");
}

void test_muxed_account_to_address_muxed_account(void **state) {
  struct MuxedAccount in = {
      .type = KEY_TYPE_MUXED_ED25519,
      .med25519 = {
          .ed25519 = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO",
          .id = 1234}};
  char out[MED25519_PUBLIC_KEY_LENGTH + 1];
  assert_true(muxed_account_to_address(&in, out));
  assert_string_equal(
      out,
      "MB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWOREAAAAAAAAAAE2K4YI");
}

void test_muxed_account_to_xdr_object_ed25519_account(void **state) {
  uint8_t ed25519_raw[] = {0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57,
                           0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46,
                           0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd,
                           0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12};
  struct MuxedAccount in = {
      .type = KEY_TYPE_ED25519,
      .ed25519 = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO"};
  stellarxdr_MuxedAccount out;
  assert_true(muxed_account_to_xdr_object(&in, &out));
  assert_int_equal(out.type, stellarxdr_KEY_TYPE_ED25519);
  assert_memory_equal(out.stellarxdr_MuxedAccount_u.ed25519, ed25519_raw, 32);
}

void test_muxed_account_to_xdr_object_muxed_account(void **state) {
  uint8_t ed25519_raw[] = {0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57,
                           0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46,
                           0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd,
                           0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12};
  struct MuxedAccount in = {
      .type = KEY_TYPE_MUXED_ED25519,
      .med25519 = {
          .ed25519 = "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO",
          .id = 1234}};
  stellarxdr_MuxedAccount out;
  assert_true(muxed_account_to_xdr_object(&in, &out));
  assert_int_equal(out.type, stellarxdr_KEY_TYPE_MUXED_ED25519);
  assert_int_equal(out.stellarxdr_MuxedAccount_u.med25519.id, 1234);
  assert_memory_equal(out.stellarxdr_MuxedAccount_u.med25519.ed25519,
                      ed25519_raw, 32);
}

void test_muxed_account_from_xdr_object_ed25519_account(void **state) {
  uint8_t ed25519_raw[] = {0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57,
                           0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46,
                           0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd,
                           0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12};
  struct MuxedAccount out;
  stellarxdr_MuxedAccount in = {
      .type = stellarxdr_KEY_TYPE_ED25519,
  };
  memcpy(in.stellarxdr_MuxedAccount_u.ed25519, ed25519_raw, 32);
  assert_true(muxed_account_from_xdr_object(&in, &out));
  assert_int_equal(out.type, KEY_TYPE_ED25519);
  assert_string_equal(
      out.ed25519, "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO");
}

void test_muxed_account_from_xdr_object_muxed_account(void **state) {
  uint8_t ed25519_raw[] = {0x7f, 0xff, 0xb1, 0x32, 0x3a, 0xff, 0x7,  0x57,
                           0x3b, 0x97, 0x74, 0xcd, 0x32, 0x2e, 0x74, 0x46,
                           0xa5, 0xc9, 0x30, 0x5f, 0x99, 0x49, 0x6,  0xbd,
                           0xfc, 0x74, 0xdb, 0x7d, 0x6e, 0x1d, 0x9d, 0x12};
  struct MuxedAccount out;
  stellarxdr_MuxedAccount in = {
      .type = stellarxdr_KEY_TYPE_MUXED_ED25519,
      .stellarxdr_MuxedAccount_u = {.med25519 = {.id = 1234}}};
  memcpy(in.stellarxdr_MuxedAccount_u.med25519.ed25519, ed25519_raw, 32);
  assert_true(muxed_account_from_xdr_object(&in, &out));
  assert_int_equal(out.type, KEY_TYPE_MUXED_ED25519);
  assert_int_equal(out.med25519.id, 1234);
  assert_string_equal(
      out.med25519.ed25519,
      "GB777MJSHL7QOVZ3S52M2MROORDKLSJQL6MUSBV57R2NW7LODWORELJO");
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_muxed_account_from_address_ed25519_account),
      cmocka_unit_test(test_muxed_account_from_address_muxed_account),
      cmocka_unit_test(test_muxed_account_to_address_ed25519_account),
      cmocka_unit_test(test_muxed_account_to_address_muxed_account),
      cmocka_unit_test(test_muxed_account_to_xdr_object_ed25519_account),
      cmocka_unit_test(test_muxed_account_to_xdr_object_muxed_account),
      cmocka_unit_test(test_muxed_account_from_xdr_object_ed25519_account),
      cmocka_unit_test(test_muxed_account_from_xdr_object_muxed_account),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
