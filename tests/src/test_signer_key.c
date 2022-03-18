#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/signer_key.h"
#include <cmocka.h>

void test_xdr_ed25519() {
  struct SignerKey signerKey = {
      .signerKeyType = SIGNER_KEY_TYPE_ED25519,
      .signerKey = {.ed25519 = {0x43, 0xd7, 0xb,  0xdc, 0xef, 0x9a, 0x2f,
                                0xfb, 0x57, 0xe6, 0xe5, 0xaf, 0x9a, 0x15,
                                0xae, 0x67, 0x35, 0xc2, 0x95, 0x9a, 0x50,
                                0xff, 0x2b, 0x34, 0xd7, 0x9a, 0xb0, 0x1f,
                                0xe5, 0x9b, 0x45, 0x70}}};
  stellarxdr_SignerKey to;
  assert_true(signer_key_to_xdr_object(&signerKey, &to));
  assert_int_equal(to.type, stellarxdr_SIGNER_KEY_TYPE_ED25519);
  assert_memory_equal(to.stellarxdr_SignerKey_u.ed25519,
                      signerKey.signerKey.ed25519, 32);
  struct SignerKey from;
  assert_true(signer_key_from_xdr_object(&to, &from));
  assert_memory_equal(&signerKey, &from, sizeof(struct SignerKey));
}

void test_xdr_preAuthTx() {
  struct SignerKey signerKey = {
      .signerKeyType = SIGNER_KEY_TYPE_PRE_AUTH_TX,
      .signerKey = {.preAuthTx = {0x43, 0xd7, 0xb,  0xdc, 0xef, 0x9a, 0x2f,
                                  0xfb, 0x57, 0xe6, 0xe5, 0xaf, 0x9a, 0x15,
                                  0xae, 0x67, 0x35, 0xc2, 0x95, 0x9a, 0x50,
                                  0xff, 0x2b, 0x34, 0xd7, 0x9a, 0xb0, 0x1f,
                                  0xe5, 0x9b, 0x45, 0x70}}};
  stellarxdr_SignerKey to;
  assert_true(signer_key_to_xdr_object(&signerKey, &to));
  assert_int_equal(to.type, stellarxdr_SIGNER_KEY_TYPE_PRE_AUTH_TX);
  assert_memory_equal(to.stellarxdr_SignerKey_u.preAuthTx,
                      signerKey.signerKey.preAuthTx, 32);
  struct SignerKey from;
  assert_true(signer_key_from_xdr_object(&to, &from));
  assert_memory_equal(&signerKey, &from, sizeof(struct SignerKey));
}

void test_xdr_hashX() {
  struct SignerKey signerKey = {
      .signerKeyType = SIGNER_KEY_TYPE_HASH_X,
      .signerKey = {.hashX = {0x43, 0xd7, 0xb,  0xdc, 0xef, 0x9a, 0x2f, 0xfb,
                              0x57, 0xe6, 0xe5, 0xaf, 0x9a, 0x15, 0xae, 0x67,
                              0x35, 0xc2, 0x95, 0x9a, 0x50, 0xff, 0x2b, 0x34,
                              0xd7, 0x9a, 0xb0, 0x1f, 0xe5, 0x9b, 0x45, 0x70}}};
  stellarxdr_SignerKey to;
  assert_true(signer_key_to_xdr_object(&signerKey, &to));
  assert_int_equal(to.type, stellarxdr_SIGNER_KEY_TYPE_HASH_X);
  assert_memory_equal(to.stellarxdr_SignerKey_u.hashX,
                      signerKey.signerKey.hashX, 32);
  struct SignerKey from;
  assert_true(signer_key_from_xdr_object(&to, &from));
  assert_memory_equal(&signerKey, &from, sizeof(struct SignerKey));
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_xdr_ed25519),
      cmocka_unit_test(test_xdr_preAuthTx),
      cmocka_unit_test(test_xdr_hashX),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
