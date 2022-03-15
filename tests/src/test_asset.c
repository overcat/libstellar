#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include "../../src/asset.h"
#include <cmocka.h>

void test_asset_to_xdr_object_native(void **state) {
  struct Asset asset = {.type = ASSET_TYPE_NATIVE};
  stellarxdr_Asset stellarxdrAsset;
  assert_true(asset_to_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_NATIVE, stellarxdrAsset.type);
}

void test_asset_from_xdr_object_native(void **state) {
  struct Asset asset = {.type = ASSET_TYPE_NATIVE};
  stellarxdr_Asset stellarxdrAsset = {.type = stellarxdr_ASSET_TYPE_NATIVE};
  assert_true(asset_from_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(ASSET_TYPE_NATIVE, asset.type);
}

void test_asset_to_xdr_object_credit_alphanum4_code_length_3(void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_Asset stellarxdrAsset;
  assert_true(asset_to_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
                   stellarxdrAsset.type);
  char code[4] = {'U', 'S', 'D', 0};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_Asset_u.alphaNum4.assetCode, 4);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(&accountId,
                      &stellarxdrAsset.stellarxdr_Asset_u.alphaNum4.issuer,
                      sizeof(stellarxdr_AccountID));
}

void test_asset_from_xdr_object_credit_alphanum4_code_length_3(void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_Asset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
      .stellarxdr_Asset_u = {
          .alphaNum4 = {
              .assetCode = "USD",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(asset_from_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}

void test_asset_to_xdr_object_credit_alphanum4_code_length_4(void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_Asset stellarxdrAsset;
  assert_true(asset_to_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
                   stellarxdrAsset.type);
  char code[4] = {'U', 'S', 'D', 'C'};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_Asset_u.alphaNum4.assetCode, 4);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(&accountId,
                      &stellarxdrAsset.stellarxdr_Asset_u.alphaNum4.issuer,
                      sizeof(stellarxdr_AccountID));
}

void test_asset_from_xdr_object_credit_alphanum4_code_length_4(void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_Asset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
      .stellarxdr_Asset_u = {
          .alphaNum4 = {
              .assetCode = "USDC",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(asset_from_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}

void test_asset_to_xdr_object_credit_alphanum12_code_length_9(void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDUSDUSD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_Asset stellarxdrAsset;
  assert_true(asset_to_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
                   stellarxdrAsset.type);
  char code[12] = {'U', 'S', 'D', 'U', 'S', 'D', 'U', 'S', 'D', 0, 0, 0};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_Asset_u.alphaNum12.assetCode, 12);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(&accountId,
                      &stellarxdrAsset.stellarxdr_Asset_u.alphaNum12.issuer,
                      sizeof(stellarxdr_AccountID));
}

void test_asset_from_xdr_object_credit_alphanum12_code_length_9(void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDUSDUSD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_Asset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
      .stellarxdr_Asset_u = {
          .alphaNum12 = {
              .assetCode = "USDUSDUSD",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(asset_from_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}

void test_asset_to_xdr_object_credit_alphanum12_code_length_12(void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDCUSDCUSDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_Asset stellarxdrAsset;
  assert_true(asset_to_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
                   stellarxdrAsset.type);
  char code[12] = {'U', 'S', 'D', 'C', 'U', 'S', 'D', 'C', 'U', 'S', 'D', 'C'};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_Asset_u.alphaNum4.assetCode, 12);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(&accountId,
                      &stellarxdrAsset.stellarxdr_Asset_u.alphaNum12.issuer,
                      sizeof(stellarxdr_AccountID));
}

void test_asset_from_xdr_object_credit_alphanum12_code_length_12(void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDCUSDCUSDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_Asset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
      .stellarxdr_Asset_u = {
          .alphaNum12 = {
              .assetCode = "USDCUSDCUSDC",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(asset_from_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}

void test_asset_to_trust_line_asset_xdr_object_native(void **state) {
  struct Asset asset = {.type = ASSET_TYPE_NATIVE};
  stellarxdr_TrustLineAsset stellarxdrAsset;
  assert_true(asset_to_trust_line_asset_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_NATIVE, stellarxdrAsset.type);
}

void test_asset_from_trust_line_asset_xdr_object_native(void **state) {
  struct Asset asset = {.type = ASSET_TYPE_NATIVE};
  stellarxdr_TrustLineAsset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_NATIVE};
  assert_true(asset_from_trust_line_asset_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(ASSET_TYPE_NATIVE, asset.type);
}

void test_asset_to_trust_line_asset_xdr_object_credit_alphanum4_code_length_3(
    void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_TrustLineAsset stellarxdrAsset;
  assert_true(asset_to_trust_line_asset_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
                   stellarxdrAsset.type);
  char code[4] = {'U', 'S', 'D', 0};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_TrustLineAsset_u.alphaNum4.assetCode, 4);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(
      &accountId, &stellarxdrAsset.stellarxdr_TrustLineAsset_u.alphaNum4.issuer,
      sizeof(stellarxdr_AccountID));
}

void test_asset_from_trust_line_asset_xdr_object_credit_alphanum4_code_length_3(
    void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_TrustLineAsset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
      .stellarxdr_TrustLineAsset_u = {
          .alphaNum4 = {
              .assetCode = "USD",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(asset_from_trust_line_asset_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}

void test_asset_to_trust_line_asset_xdr_object_credit_alphanum4_code_length_4(
    void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_TrustLineAsset stellarxdrAsset;
  assert_true(asset_to_trust_line_asset_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
                   stellarxdrAsset.type);
  char code[4] = {'U', 'S', 'D', 'C'};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_TrustLineAsset_u.alphaNum4.assetCode, 4);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(
      &accountId, &stellarxdrAsset.stellarxdr_TrustLineAsset_u.alphaNum4.issuer,
      sizeof(stellarxdr_AccountID));
}

void test_asset_from_trust_line_asset_xdr_object_credit_alphanum4_code_length_4(
    void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_TrustLineAsset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
      .stellarxdr_TrustLineAsset_u = {
          .alphaNum4 = {
              .assetCode = "USDC",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(asset_from_trust_line_asset_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}

void test_asset_to_trust_line_asset_xdr_object_credit_alphanum12_code_length_9(
    void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDUSDUSD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_TrustLineAsset stellarxdrAsset;
  assert_true(asset_to_trust_line_asset_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
                   stellarxdrAsset.type);
  char code[12] = {'U', 'S', 'D', 'U', 'S', 'D', 'U', 'S', 'D', 0, 0, 0};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_TrustLineAsset_u.alphaNum12.assetCode,
      12);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(
      &accountId,
      &stellarxdrAsset.stellarxdr_TrustLineAsset_u.alphaNum12.issuer,
      sizeof(stellarxdr_AccountID));
}

void test_asset_from_trust_line_asset_xdr_object_credit_alphanum12_code_length_9(
    void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDUSDUSD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_TrustLineAsset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
      .stellarxdr_TrustLineAsset_u = {
          .alphaNum12 = {
              .assetCode = "USDUSDUSD",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(asset_from_trust_line_asset_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}

void test_asset_to_trust_line_asset_xdr_object_credit_alphanum12_code_length_12(
    void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDCUSDCUSDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_TrustLineAsset stellarxdrAsset;
  assert_true(asset_to_trust_line_asset_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
                   stellarxdrAsset.type);
  char code[12] = {'U', 'S', 'D', 'C', 'U', 'S', 'D', 'C', 'U', 'S', 'D', 'C'};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_TrustLineAsset_u.alphaNum4.assetCode,
      12);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(
      &accountId,
      &stellarxdrAsset.stellarxdr_TrustLineAsset_u.alphaNum12.issuer,
      sizeof(stellarxdr_AccountID));
}

void test_asset_from_trust_line_asset_xdr_object_credit_alphanum12_code_length_12(
    void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDCUSDCUSDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_TrustLineAsset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
      .stellarxdr_TrustLineAsset_u = {
          .alphaNum12 = {
              .assetCode = "USDCUSDCUSDC",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(asset_from_trust_line_asset_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}

void test_asset_to_change_trust_asset_xdr_object_native(void **state) {
  struct Asset asset = {.type = ASSET_TYPE_NATIVE};
  stellarxdr_ChangeTrustAsset stellarxdrAsset;
  assert_true(asset_to_change_trust_asset_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_NATIVE, stellarxdrAsset.type);
}

void test_asset_from_change_trust_asset_xdr_object_native(void **state) {
  struct Asset asset = {.type = ASSET_TYPE_NATIVE};
  stellarxdr_ChangeTrustAsset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_NATIVE};
  assert_true(
      asset_from_change_trust_asset_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(ASSET_TYPE_NATIVE, asset.type);
}

void test_asset_to_change_trust_asset_xdr_object_credit_alphanum4_code_length_3(
    void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_ChangeTrustAsset stellarxdrAsset;
  assert_true(asset_to_change_trust_asset_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
                   stellarxdrAsset.type);
  char code[4] = {'U', 'S', 'D', 0};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_ChangeTrustAsset_u.alphaNum4.assetCode,
      4);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(
      &accountId,
      &stellarxdrAsset.stellarxdr_ChangeTrustAsset_u.alphaNum4.issuer,
      sizeof(stellarxdr_AccountID));
}

void test_asset_from_change_trust_asset_xdr_object_credit_alphanum4_code_length_3(
    void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_ChangeTrustAsset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
      .stellarxdr_ChangeTrustAsset_u = {
          .alphaNum4 = {
              .assetCode = "USD",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(
      asset_from_change_trust_asset_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}

void test_asset_to_change_trust_asset_xdr_object_credit_alphanum4_code_length_4(
    void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_ChangeTrustAsset stellarxdrAsset;
  assert_true(asset_to_change_trust_asset_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
                   stellarxdrAsset.type);
  char code[4] = {'U', 'S', 'D', 'C'};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_ChangeTrustAsset_u.alphaNum4.assetCode,
      4);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(
      &accountId,
      &stellarxdrAsset.stellarxdr_ChangeTrustAsset_u.alphaNum4.issuer,
      sizeof(stellarxdr_AccountID));
}

void test_asset_from_change_trust_asset_xdr_object_credit_alphanum4_code_length_4(
    void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM4,
      .code = "USDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_ChangeTrustAsset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM4,
      .stellarxdr_ChangeTrustAsset_u = {
          .alphaNum4 = {
              .assetCode = "USDC",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(
      asset_from_change_trust_asset_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}

void test_asset_to_change_trust_asset_xdr_object_credit_alphanum12_code_length_9(
    void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDUSDUSD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_ChangeTrustAsset stellarxdrAsset;
  assert_true(asset_to_change_trust_asset_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
                   stellarxdrAsset.type);
  char code[12] = {'U', 'S', 'D', 'U', 'S', 'D', 'U', 'S', 'D', 0, 0, 0};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_ChangeTrustAsset_u.alphaNum12.assetCode,
      12);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(
      &accountId,
      &stellarxdrAsset.stellarxdr_ChangeTrustAsset_u.alphaNum12.issuer,
      sizeof(stellarxdr_AccountID));
}

void test_asset_from_change_trust_asset_xdr_object_credit_alphanum12_code_length_9(
    void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDUSDUSD",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_ChangeTrustAsset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
      .stellarxdr_ChangeTrustAsset_u = {
          .alphaNum12 = {
              .assetCode = "USDUSDUSD",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(
      asset_from_change_trust_asset_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}

void test_asset_to_change_trust_asset_xdr_object_credit_alphanum12_code_length_12(
    void **state) {
  struct Asset asset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDCUSDCUSDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  stellarxdr_ChangeTrustAsset stellarxdrAsset;
  assert_true(asset_to_change_trust_asset_xdr_object(&asset, &stellarxdrAsset));
  assert_int_equal(stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
                   stellarxdrAsset.type);
  char code[12] = {'U', 'S', 'D', 'C', 'U', 'S', 'D', 'C', 'U', 'S', 'D', 'C'};
  assert_memory_equal(
      code, stellarxdrAsset.stellarxdr_ChangeTrustAsset_u.alphaNum4.assetCode,
      12);
  stellarxdr_AccountID accountId = {
      .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
      .stellarxdr_PublicKey_u = {
          .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98, 0x8b,
                      0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf, 0xe4, 0x4f,
                      0x36, 0x6f, 0x7d, 0xbe, 0x94, 0x6b, 0xed, 0x7,
                      0x72, 0x40, 0xf7, 0xf6, 0x24, 0xdf, 0x15, 0xc5}}};
  assert_memory_equal(
      &accountId,
      &stellarxdrAsset.stellarxdr_ChangeTrustAsset_u.alphaNum12.issuer,
      sizeof(stellarxdr_AccountID));
}

void test_asset_from_change_trust_asset_xdr_object_credit_alphanum12_code_length_12(
    void **state) {
  struct Asset expectAsset = {
      .type = ASSET_TYPE_CREDIT_ALPHANUM12,
      .code = "USDCUSDCUSDC",
      .issuer = "GA5ZSEJYB37JRC5AVCIA5MOP4RHTM335X2KGX3IHOJAPP5RE34K4KZVN"};
  struct Asset asset;
  stellarxdr_ChangeTrustAsset stellarxdrAsset = {
      .type = stellarxdr_ASSET_TYPE_CREDIT_ALPHANUM12,
      .stellarxdr_ChangeTrustAsset_u = {
          .alphaNum12 = {
              .assetCode = "USDCUSDCUSDC",
              .issuer = {
                  .type = stellarxdr_PUBLIC_KEY_TYPE_ED25519,
                  .stellarxdr_PublicKey_u = {
                      .ed25519 = {0x3b, 0x99, 0x11, 0x38, 0xe,  0xfe, 0x98,
                                  0x8b, 0xa0, 0xa8, 0x90, 0xe,  0xb1, 0xcf,
                                  0xe4, 0x4f, 0x36, 0x6f, 0x7d, 0xbe, 0x94,
                                  0x6b, 0xed, 0x7,  0x72, 0x40, 0xf7, 0xf6,
                                  0x24, 0xdf, 0x15, 0xc5}}}}}};
  assert_true(asset_from_trust_line_asset_xdr_object(&stellarxdrAsset, &asset));
  assert_int_equal(asset.type, expectAsset.type);
  assert_string_equal(asset.code, expectAsset.code);
  assert_string_equal(asset.issuer, expectAsset.issuer);
}
int main() {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_asset_to_xdr_object_native),
      cmocka_unit_test(test_asset_to_xdr_object_credit_alphanum4_code_length_3),
      cmocka_unit_test(test_asset_to_xdr_object_credit_alphanum4_code_length_4),
      cmocka_unit_test(
          test_asset_to_xdr_object_credit_alphanum12_code_length_9),
      cmocka_unit_test(
          test_asset_to_xdr_object_credit_alphanum12_code_length_12),

      cmocka_unit_test(test_asset_from_xdr_object_native),
      cmocka_unit_test(
          test_asset_from_xdr_object_credit_alphanum4_code_length_3),
      cmocka_unit_test(
          test_asset_from_xdr_object_credit_alphanum4_code_length_4),
      cmocka_unit_test(
          test_asset_from_xdr_object_credit_alphanum12_code_length_9),
      cmocka_unit_test(
          test_asset_from_xdr_object_credit_alphanum12_code_length_12),

      cmocka_unit_test(test_asset_to_trust_line_asset_xdr_object_native),
      cmocka_unit_test(
          test_asset_to_trust_line_asset_xdr_object_credit_alphanum4_code_length_3),
      cmocka_unit_test(
          test_asset_to_trust_line_asset_xdr_object_credit_alphanum4_code_length_4),
      cmocka_unit_test(
          test_asset_to_trust_line_asset_xdr_object_credit_alphanum12_code_length_9),
      cmocka_unit_test(
          test_asset_to_trust_line_asset_xdr_object_credit_alphanum12_code_length_12),

      cmocka_unit_test(test_asset_from_trust_line_asset_xdr_object_native),
      cmocka_unit_test(
          test_asset_from_trust_line_asset_xdr_object_credit_alphanum4_code_length_3),
      cmocka_unit_test(
          test_asset_from_trust_line_asset_xdr_object_credit_alphanum4_code_length_4),
      cmocka_unit_test(
          test_asset_from_trust_line_asset_xdr_object_credit_alphanum12_code_length_9),
      cmocka_unit_test(
          test_asset_from_trust_line_asset_xdr_object_credit_alphanum12_code_length_12),

      cmocka_unit_test(test_asset_to_change_trust_asset_xdr_object_native),
      cmocka_unit_test(
          test_asset_to_change_trust_asset_xdr_object_credit_alphanum4_code_length_3),
      cmocka_unit_test(
          test_asset_to_change_trust_asset_xdr_object_credit_alphanum4_code_length_4),
      cmocka_unit_test(
          test_asset_to_change_trust_asset_xdr_object_credit_alphanum12_code_length_9),
      cmocka_unit_test(
          test_asset_to_change_trust_asset_xdr_object_credit_alphanum12_code_length_12),

      cmocka_unit_test(test_asset_from_change_trust_asset_xdr_object_native),
      cmocka_unit_test(
          test_asset_from_change_trust_asset_xdr_object_credit_alphanum4_code_length_3),
      cmocka_unit_test(
          test_asset_from_change_trust_asset_xdr_object_credit_alphanum4_code_length_4),
      cmocka_unit_test(
          test_asset_from_change_trust_asset_xdr_object_credit_alphanum12_code_length_9),
      cmocka_unit_test(
          test_asset_from_change_trust_asset_xdr_object_credit_alphanum12_code_length_12),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
