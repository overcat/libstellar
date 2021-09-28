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

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_muxed_account_from_address_ed25519_account),
      cmocka_unit_test(test_muxed_account_from_address_muxed_account),
      cmocka_unit_test(test_muxed_account_to_address_ed25519_account),
      cmocka_unit_test(test_muxed_account_to_address_muxed_account),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
