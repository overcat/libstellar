#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/liquidity_pool_asset.h"
#include <cmocka.h>
bool _liquidity_pool_asset_to_xdr(const struct LiquidityPoolAsset *in,
                                  char **buf, size_t *buf_size) {
  stellarxdr_ChangeTrustAsset changeTrustAsset;
  liquidity_pool_asset_to_change_trust_asset_xdr_object(in, &changeTrustAsset);
  FILE *fp = open_memstream(buf, buf_size);
  XDR xdr;
  xdrstdio_create(&xdr, fp, XDR_ENCODE);
  if (!xdr_stellarxdr_ChangeTrustAsset(&xdr, &changeTrustAsset)) {
    fclose(fp);
    return false;
  }
  fclose(fp);
  return true;
}

void test_liquidity_pool_asset_change_trust_asset_xdr_object(void **state) {
  struct Asset assetA = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};

  struct Asset assetB = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct LiquidityPoolAsset liquidityPoolAsset = {
      .assetA = assetA, .assetB = assetB, .fee = LIQUIDITY_POOL_FEE_V18};

  char *buf0 = NULL;
  size_t buf_size0 = 0;
  assert_true(
      _liquidity_pool_asset_to_xdr(&liquidityPoolAsset, &buf0, &buf_size0));
  char xdr[] = {0x0,  0x0,  0x0,  0x3,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
                0x0,  0x1,  0x55, 0x53, 0x44, 0x0,  0x0,  0x0,  0x0,  0x0,
                0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b, 0xa0, 0xa8,
                0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe,
                0x94, 0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf,
                0x15, 0xc5, 0x0,  0x0,  0x0,  0x1,  0x55, 0x53, 0x44, 0x43,
                0x0,  0x0,  0x0,  0x0,  0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe,
                0x98, 0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,  0x72, 0x40,
                0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5, 0x0,  0x0,  0x0,  0x1e};
  assert_int_equal(buf_size0, 100);
  assert_memory_equal(buf0, xdr, buf_size0);

  stellarxdr_ChangeTrustAsset to;
  assert_true(liquidity_pool_asset_to_change_trust_asset_xdr_object(
      &liquidityPoolAsset, &to));
  struct LiquidityPoolAsset from;
  assert_true(
      liquidity_pool_asset_from_change_trust_asset_xdr_object(&to, &from));
  char *buf1 = NULL;
  size_t buf_size1 = 0;
  assert_true(_liquidity_pool_asset_to_xdr(&from, &buf1, &buf_size1));
  assert_int_equal(buf_size1, 100);
  assert_memory_equal(buf1, xdr, buf_size1);
}

int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_liquidity_pool_asset_change_trust_asset_xdr_object),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
