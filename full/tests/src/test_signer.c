#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/signer.h"
#include "../../src/signer_key.h"
#include <cmocka.h>

void test_signer_xdr() {
  struct SignerKey signerKey = {
      .signerKeyType = SIGNER_KEY_TYPE_ED25519,
      .signerKey = {.ed25519 = {0x43, 0xd7, 0xb,  0xdc, 0xef, 0x9a, 0x2f,
                                0xfb, 0x57, 0xe6, 0xe5, 0xaf, 0x9a, 0x15,
                                0xae, 0x67, 0x35, 0xc2, 0x95, 0x9a, 0x50,
                                0xff, 0x2b, 0x34, 0xd7, 0x9a, 0xb0, 0x1f,
                                0xe5, 0x9b, 0x45, 0x70}}};
  struct Signer signer = {.key = signerKey, .weight = 255};

  stellarxdr_Signer to;
  assert_true(signer_to_xdr_object(&signer, &to));
  assert_int_equal(to.weight, 255);
  assert_memory_equal(to.key.stellarxdr_SignerKey_u.ed25519,
                      signerKey.signerKey.ed25519, 32);
  struct Signer from;
  assert_true(signer_from_xdr_object(&to, &from));
  assert_memory_equal(&signerKey, &from, sizeof(struct SignerKey));
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_signer_xdr),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
