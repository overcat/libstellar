#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <cmocka.h>

#include "../src/types.h"
#include "../src/utils.h"

static void test_encode_ed25519_public_key() {
    uint8_t raw_key[] = {0xe9, 0x33, 0x88, 0xbb, 0xfd, 0x2f, 0xbd, 0x11, 0x80, 0x6d, 0xd0,
                         0xbd, 0x59, 0xce, 0xa9, 0x7,  0x9e, 0x7c, 0xc7, 0xc,  0xe7, 0xb1,
                         0xe1, 0x54, 0xf1, 0x14, 0xcd, 0xfe, 0x4e, 0x46, 0x6e, 0xcd};
    char *encoded_key = "GDUTHCF37UX32EMANXIL2WOOVEDZ47GHBTT3DYKU6EKM37SOIZXM2FN7";
    char out[ENCODED_ED25519_PUBLIC_KEY_LENGTH];
    size_t out_len = sizeof(out);
    assert_true(encode_ed25519_public_key(raw_key, out, out_len));
    assert_string_equal(out, encoded_key);
}

static void test_encode_hash_x_key() {
    uint8_t raw_key[] = {0xe9, 0x33, 0x88, 0xbb, 0xfd, 0x2f, 0xbd, 0x11, 0x80, 0x6d, 0xd0,
                         0xbd, 0x59, 0xce, 0xa9, 0x7,  0x9e, 0x7c, 0xc7, 0xc,  0xe7, 0xb1,
                         0xe1, 0x54, 0xf1, 0x14, 0xcd, 0xfe, 0x4e, 0x46, 0x6e, 0xcd};
    char *encoded_key = "XDUTHCF37UX32EMANXIL2WOOVEDZ47GHBTT3DYKU6EKM37SOIZXM242X";
    char out[ENCODED_ED25519_PUBLIC_KEY_LENGTH];
    size_t out_len = sizeof(out);
    assert_true(encode_hash_x_key(raw_key, out, out_len));
    assert_string_equal(out, encoded_key);
}

static void test_encode_pre_auth_x_key() {
    uint8_t raw_key[] = {0xe9, 0x33, 0x88, 0xbb, 0xfd, 0x2f, 0xbd, 0x11, 0x80, 0x6d, 0xd0,
                         0xbd, 0x59, 0xce, 0xa9, 0x7,  0x9e, 0x7c, 0xc7, 0xc,  0xe7, 0xb1,
                         0xe1, 0x54, 0xf1, 0x14, 0xcd, 0xfe, 0x4e, 0x46, 0x6e, 0xcd};
    char *encoded_key = "TDUTHCF37UX32EMANXIL2WOOVEDZ47GHBTT3DYKU6EKM37SOIZXM3Y7O";
    char out[ENCODED_ED25519_PUBLIC_KEY_LENGTH];
    size_t out_len = sizeof(out);
    assert_true(encode_pre_auth_x_key(raw_key, out, out_len));
    assert_string_equal(out, encoded_key);
}

static void test_encode_muxed_account() {
    // https://github.com/stellar/stellar-protocol/blob/master/ecosystem/sep-0023.md#valid-test-cases
    char out[89];
    // GA7QYNF7SOWQ3GLR2BGMZEHXAVIRZA4KVWLTJJFC7MGXUA74P7UJVSGZ
    const uint8_t ed25519[] = {
        0x3f, 0x0c, 0x34, 0xbf, 0x93, 0xad, 0x0d, 0x99, 0x71, 0xd0, 0x4c,
        0xcc, 0x90, 0xf7, 0x05, 0x51, 0x1c, 0x83, 0x8a, 0xad, 0x97, 0x34,
        0xa4, 0xa2, 0xfb, 0x0d, 0x7a, 0x03, 0xfc, 0x7f, 0xe8, 0x9a,
    };
    // Valid non-multiplexed account
    muxed_account_t account1 = {.type = KEY_TYPE_ED25519, .ed25519 = ed25519};
    assert_true(encode_muxed_account(&account1, out, sizeof(out)));
    assert_string_equal(out, "GA7QYNF7SOWQ3GLR2BGMZEHXAVIRZA4KVWLTJJFC7MGXUA74P7UJVSGZ");

    // Valid multiplexed account
    muxed_account_t account2 = {.type = KEY_TYPE_MUXED_ED25519,
                             .med25519 = {.id = 0, .ed25519 = ed25519}};
    assert_true(encode_muxed_account(&account2, out, sizeof(out)));
    assert_string_equal(out,
                        "MA7QYNF7SOWQ3GLR2BGMZEHXAVIRZA4KVWLTJJFC7MGXUA74P7UJUAAAAAAAAAAAACJUQ");

    // Valid multiplexed account in which unsigned id exceeds maximum signed 64-bit integer
    muxed_account_t account3 = {.type = KEY_TYPE_MUXED_ED25519,
                             .med25519 = {.id = 9223372036854775808, .ed25519 = ed25519}};
    assert_true(encode_muxed_account(&account3, out, sizeof(out)));
    assert_string_equal(out,
                        "MA7QYNF7SOWQ3GLR2BGMZEHXAVIRZA4KVWLTJJFC7MGXUA74P7UJVAAAAAAAAAAAAAJLK");
}

void test_print_binary() {
    const uint8_t binary[32] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
                                16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    char hex[2 * sizeof(binary) + 1];

    assert_true(print_binary(binary, sizeof(binary), hex, sizeof(hex), 0, 0));
    assert_string_equal(hex, "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f");
}

void test_print_claimable_balance_id() {
    claimable_balance_id_t id = {
        .type = CLAIMABLE_BALANCE_ID_TYPE_V0,
        .v0 = {0xc9, 0xc4, 0xa9, 0xe3, 0xa4, 0x68, 0x91, 0xa3, 0x60, 0x15, 0xc3,
               0x17, 0xb3, 0xdf, 0x17, 0xb4, 0x2b, 0xf,  0x2a, 0xd8, 0xa2, 0xee,
               0xa6, 0xc9, 0x34, 0xc9, 0xf7, 0xc8, 0x42, 0x5d, 0xa7, 0xad}};

    char out[36 * 2 + 1];
    assert_true(print_claimable_balance_id(&id, out, sizeof(out)));
    assert_string_equal(out,
                        "00000000c9c4a9e3a46891a36015c317b3df17b42b0f2ad8a2eea6c934c9f7c8425da7ad");
}

void test_print_time() {
    char out[20];
    assert_true(print_time(0, out, sizeof(out)));
    assert_string_equal(out, "1970-01-01 00:00:00");
    assert_true(print_time(1648263853, out, sizeof(out)));
    assert_string_equal(out, "2022-03-26 03:04:13");
    assert_true(print_time(2147483647, out, sizeof(out)));
    assert_string_equal(out, "2038-01-19 03:14:07");
    assert_true(print_time(4294967295, out, sizeof(out)));
    assert_string_equal(out, "2106-02-07 06:28:15");
    assert_true(print_time(253402300799, out, sizeof(out)));
    assert_string_equal(out, "9999-12-31 23:59:59");
    assert_false(print_time(253402300800, out, sizeof(out)));
    assert_false(print_time(18446744073709551615, out, sizeof(out)));
}

void test_print_uint() {
    char out[24];

    assert_true(print_uint(0, out, sizeof(out)));
    assert_string_equal(out, "0");

    assert_true(print_uint(1230, out, sizeof(out)));
    assert_string_equal(out, "1230");

    assert_true(print_uint((uint64_t) 18446744073709551615, out, sizeof(out)));
    assert_string_equal(out, "18446744073709551615");

    // output buffer too small
    assert_false(print_uint(1230, out, 4));

    // output buffer just big enough to store output data
    assert_true(print_uint(9999, out, 5));
    assert_string_equal(out, "9999");

    // output buffer just big enough to store output data
    assert_true(print_uint(9999, out, 5));
    assert_string_equal(out, "9999");
}

void test_print_int() {
    char out[24];

    assert_true(print_int((int64_t) 0, out, sizeof(out)));
    assert_string_equal(out, "0");

    assert_true(print_int((int64_t) 1230, out, sizeof(out)));
    assert_string_equal(out, "1230");

    assert_true(print_int((int64_t) -1230, out, sizeof(out)));
    assert_string_equal(out, "-1230");

    assert_true(print_int((int64_t) 9223372036854775807, out, sizeof(out)));
    assert_string_equal(out, "9223372036854775807");

    assert_true(print_int((int64_t) -9223372036854775808, out, sizeof(out)));
    assert_string_equal(out, "-9223372036854775808");

    // output buffer too small
    assert_false(print_int((int64_t) -1230, out, 5));
    assert_false(print_int(1230, out, 4));

    // output buffer just big enough to store output data
    assert_true(print_int((int64_t) -9999, out, 6));
    assert_string_equal(out, "-9999");
    assert_true(print_int((int64_t) 9999, out, 5));
    assert_string_equal(out, "9999");
}

void test_print_asset() {
    asset_t assert_native = {.type = ASSET_TYPE_NATIVE};
    char out[24];
    assert_true(print_asset(&assert_native, out, sizeof(out)));
    assert_string_equal(out, "XLM");

    const uint8_t ed25519[] = {
        0x3f, 0x0c, 0x34, 0xbf, 0x93, 0xad, 0x0d, 0x99, 0x71, 0xd0, 0x4c,
        0xcc, 0x90, 0xf7, 0x05, 0x51, 0x1c, 0x83, 0x8a, 0xad, 0x97, 0x34,
        0xa4, 0xa2, 0xfb, 0x0d, 0x7a, 0x03, 0xfc, 0x7f, 0xe8, 0x9a,
    };
    asset_t assert_alphanum4 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                              .alpha_num4 = {.asset_code = "CAT", .issuer = ed25519}};
    assert_true(print_asset(&assert_alphanum4, out, sizeof(out)));
    assert_string_equal(out, "CAT@GA7..VSGZ");

    asset_t assert_alphanum12 = {.type = ASSET_TYPE_CREDIT_ALPHANUM12,
                               .alpha_num12 = {.asset_code = "BANANANANANA", .issuer = ed25519}};
    assert_true(print_asset(&assert_alphanum12, out, sizeof(out)));
    assert_string_equal(out, "BANANANANANA@GA7..VSGZ");
}

void test_print_summary() {
    char *data1 = "abcdefghijklmnopqrstuvwxyz";
    char out1[10];
    assert_true(print_summary(data1, out1, sizeof(out1), 3, 4));
    assert_string_equal(out1, "abc..wxyz");

    char *data2 = "abcdef";
    char out2[11];
    assert_true(print_summary(data2, out2, sizeof(out2), 4, 4));
    assert_string_equal(out2, "abcdef");

    char *data3 = "abcdefghijklmnopqrstuvwxyz";
    char out3[10];
    assert_false(print_summary(data3, out3, sizeof(out3), 4, 4));
}

int main() {
    const struct CMUnitTest tests[] = {cmocka_unit_test(test_encode_ed25519_public_key),
                                       cmocka_unit_test(test_encode_hash_x_key),
                                       cmocka_unit_test(test_encode_pre_auth_x_key),
                                       cmocka_unit_test(test_encode_muxed_account),
                                       cmocka_unit_test(test_print_binary),
                                       cmocka_unit_test(test_print_claimable_balance_id),
                                       cmocka_unit_test(test_print_time),
                                       cmocka_unit_test(test_print_uint),
                                       cmocka_unit_test(test_print_int),
                                       cmocka_unit_test(test_print_asset),
                                       cmocka_unit_test(test_print_summary)};
    return cmocka_run_group_tests(tests, NULL, NULL);
}