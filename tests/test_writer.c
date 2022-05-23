#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <cmocka.h>

#include "../src/types.h"
#include "../src/writer.h"

#include "include/sha256.h"

SHA256_CTX sha256_ctx;
uint8_t hash[32] = {0};
void sha256_update_f(const uint8_t *data, size_t len) {
    sha256_update(&sha256_ctx, data, len);
}

uint8_t kp1_public[] = {0x62, 0x5f, 0x3d, 0x59, 0xc3, 0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda,
                        0x5e, 0x8,  0xc5, 0xd6, 0xe4, 0xbd, 0xf0, 0xd1, 0x50, 0x3a, 0xb9,
                        0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb, 0x9,  0x1e, 0x5d, 0xa1};
uint8_t kp2_public[] = {0xb4, 0x69, 0xf8, 0x27, 0xc2, 0x68, 0xa1, 0xfe, 0x55, 0x2,  0xaf,
                        0x55, 0x87, 0x1,  0x11, 0x16, 0x23, 0xe3, 0xbf, 0xf8, 0x81, 0x74,
                        0xb3, 0xb0, 0x6d, 0x56, 0x48, 0x8c, 0xc5, 0x2e, 0xfe, 0xb8};

static void test_create_account_op() {
    operation_t operation = {.type = OPERATION_TYPE_CREATE_ACCOUNT,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .create_account_op = {
                                 .destination = kp2_public,
                                 .starting_balance = 12345678900,
                             }};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xbc, 0x7f, 0x51, 0x59, 0xdb, 0x7c, 0xdc, 0xf7, 0x26, 0x27, 0x16,
                             0x86, 0xfb, 0x14, 0xe4, 0x14, 0xdc, 0x7d, 0xb7, 0x91, 0xd4, 0xb,
                             0x41, 0x69, 0x1c, 0x8,  0xc4, 0x9e, 0xe9, 0xa9, 0xad, 0x45};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_payment_op() {
    operation_t operation = {
        .type = OPERATION_TYPE_PAYMENT,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .payment_op = {.destination = {.type = KEY_TYPE_ED25519, .ed25519 = kp2_public},
                       .amount = 100000000000,
                       .asset = {.type = ASSET_TYPE_NATIVE}}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xde, 0x4d, 0x0,  0x24, 0x8a, 0x20, 0x25, 0x8c, 0xb9, 0x6a, 0xf6,
                             0xad, 0xe4, 0xf2, 0x8,  0xde, 0x52, 0x86, 0x8a, 0x82, 0x33, 0xc3,
                             0x84, 0x1c, 0x45, 0xf7, 0x65, 0xe,  0x25, 0x7c, 0x96, 0x5d};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_path_payment_strict_receive_op() {
    uint8_t issuer1[] = {0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4,
                         0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3,
                         0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8};
    uint8_t issuer2[] = {0xd3, 0x52, 0x8c, 0xdd, 0x70, 0xad, 0xd7, 0xe2, 0xc7, 0xf,  0xb8,
                         0xc3, 0x4c, 0xe6, 0x29, 0x7b, 0xf1, 0xc6, 0x29, 0x20, 0xe8, 0x42,
                         0x8c, 0x8b, 0xd4, 0x96, 0xd4, 0x39, 0xcd, 0x3e, 0x13, 0x63};
    uint8_t issuer3[] = {0xd3, 0x52, 0x8c, 0xdd, 0x70, 0xad, 0xd7, 0xe2, 0xc7, 0xf,  0xb8,
                         0xc3, 0x4c, 0xe6, 0x29, 0x7b, 0xf1, 0xc6, 0x29, 0x20, 0xe8, 0x42,
                         0x8c, 0x8b, 0xd4, 0x96, 0xd4, 0x39, 0xcd, 0x3e, 0x13, 0x63};
    asset_t asset1 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                      .alpha_num4 = {.asset_code = "USD", .issuer = issuer1}};
    asset_t asset2 = {.type = ASSET_TYPE_CREDIT_ALPHANUM12,
                      .alpha_num12 = {.asset_code = "CATCOIN", .issuer = issuer2}};
    asset_t asset3 = {.type = ASSET_TYPE_CREDIT_ALPHANUM12,
                      .alpha_num12 = {.asset_code = "PANDA", .issuer = issuer3}};

    operation_t operation = {.type = OPERATION_TYPE_PATH_PAYMENT_STRICT_RECEIVE,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .path_payment_strict_receive_op = {
                                 .destination = {.type = KEY_TYPE_ED25519, .ed25519 = kp2_public},
                                 .send_asset = {.type = ASSET_TYPE_NATIVE},
                                 .send_max = 1000000000,
                                 .dest_asset = asset1,
                                 .dest_amount = 2000000000,
                                 .path_len = 2,
                             }};
    memcpy(&operation.path_payment_strict_receive_op.path[0], &asset2, sizeof(asset2));
    memcpy(&operation.path_payment_strict_receive_op.path[1], &asset3, sizeof(asset3));

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xf8, 0x89, 0x22, 0x6,  0xc5, 0x54, 0x8e, 0x1d, 0xf7, 0xf5, 0x75,
                             0xe4, 0x25, 0x24, 0x71, 0x71, 0xc2, 0xde, 0x31, 0x54, 0x21, 0x67,
                             0xc6, 0x26, 0x1f, 0xc4, 0xac, 0xb0, 0xd1, 0x1e, 0xeb, 0x51};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_account_op),
        cmocka_unit_test(test_payment_op),
        cmocka_unit_test(test_path_payment_strict_receive_op),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}