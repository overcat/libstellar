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

static void test_manage_sell_offer_op() {
    uint8_t issuer1[] = {0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4,
                         0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3,
                         0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8};
    asset_t asset1 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                      .alpha_num4 = {.asset_code = "USD", .issuer = issuer1}};

    operation_t operation = {.type = OPERATION_TYPE_MANAGE_SELL_OFFER,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .manage_sell_offer_op = {
                                 .selling = {.type = ASSET_TYPE_NATIVE},
                                 .buying = asset1,
                                 .amount = 100000000,
                                 .price = {.n = 1, .d = 1},
                                 .offer_id = 123456,
                             }};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xf4, 0x6b, 0xa6, 0xa2, 0x1b, 0x49, 0x89, 0x6,  0x23, 0x7f, 0xf0,
                             0x1b, 0x4e, 0x4a, 0xcd, 0xee, 0x11, 0x45, 0x35, 0xee, 0x4f, 0x8,
                             0x5c, 0xcb, 0x28, 0x22, 0xb3, 0x8c, 0x9,  0x76, 0xcd, 0xc1};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_create_passive_sell_offer_op() {
    uint8_t issuer1[] = {0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4,
                         0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3,
                         0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8};
    asset_t asset1 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                      .alpha_num4 = {.asset_code = "USD", .issuer = issuer1}};

    operation_t operation = {.type = OPERATION_TYPE_CREATE_PASSIVE_SELL_OFFER,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .create_passive_sell_offer_op = {
                                 .selling = {.type = ASSET_TYPE_NATIVE},
                                 .buying = asset1,
                                 .amount = 100000000,
                                 .price = {.n = 1, .d = 1},
                             }};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x29, 0xa4, 0x32, 0x47, 0x94, 0x28, 0x59, 0xae, 0x92, 0x62, 0x6e,
                             0x38, 0xbd, 0x6e, 0x7d, 0x96, 0xc,  0xfc, 0x8f, 0xcd, 0xae, 0x9a,
                             0xc9, 0xc9, 0xa9, 0x87, 0x3d, 0xbb, 0x67, 0x6,  0x67, 0xc3};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_change_trust_op() {
    uint8_t issuer1[] = {0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4,
                         0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3,
                         0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8};
    change_trust_asset_t asset1 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                                   .alpha_num4 = {.asset_code = "USD", .issuer = issuer1}};

    operation_t operation = {.type = OPERATION_TYPE_CHANGE_TRUST,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .change_trust_op = {
                                 .line = asset1,
                                 .limit = 100000000,
                             }};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x3a, 0x93, 0xa,  0xa2, 0xc3, 0x8a, 0xbe, 0xa6, 0xf7, 0x66, 0xc4,
                             0x8f, 0x99, 0x94, 0x72, 0x70, 0xec, 0x88, 0x69, 0xb,  0xfb, 0x88,
                             0x80, 0x52, 0x44, 0x45, 0xd7, 0x84, 0xb,  0x17, 0xbd, 0xa};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_allow_trust_op() {
    operation_t operation = {.type = OPERATION_TYPE_ALLOW_TRUST,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .allow_trust_op = {.trustor = kp2_public,
                                                .asset_code = "USD",
                                                .authorize = AUTHORIZED_FLAG}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x97, 0x53, 0x5f, 0x4f, 0xe3, 0x25, 0xbe, 0x20, 0xb3, 0x8d, 0x45,
                             0x83, 0xde, 0x12, 0x53, 0xb8, 0xf5, 0x15, 0x49, 0x51, 0x4c, 0xa,
                             0x86, 0xc5, 0xee, 0xf8, 0x8c, 0x51, 0x90, 0x60, 0xa6, 0xa9};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_account_merge_op() {
    operation_t operation = {.type = OPERATION_TYPE_ACCOUNT_MERGE,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .account_merge_op = {.destination = {
                                                      .type = KEY_TYPE_ED25519,
                                                      .ed25519 = kp2_public,
                                                  }}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xe,  0x2,  0x8f, 0x18, 0xa7, 0x9e, 0xc6, 0x7e, 0xe9, 0xe0, 0x76,
                             0xb5, 0x1a, 0x3d, 0xd0, 0xf7, 0xf0, 0x3c, 0x53, 0x97, 0x3d, 0x82,
                             0xec, 0x8,  0x1,  0x22, 0xc4, 0xed, 0xc2, 0xe5, 0x7c, 0xc9};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_inflation_op() {
    operation_t operation = {
        .type = OPERATION_TYPE_INFLATION,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
    };

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x17, 0x43, 0xaf, 0x1,  0x5d, 0x59, 0xb6, 0x6,  0xbd, 0x16, 0x97,
                             0xfd, 0x0,  0xc4, 0x1,  0x41, 0x1d, 0x35, 0xa8, 0x6f, 0x98, 0xab,
                             0x68, 0x6b, 0x8d, 0x3e, 0xb9, 0x48, 0x15, 0xfd, 0xbf, 0xf};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_manage_data_set_data() {
    uint8_t data_name[] = "hello";
    uint8_t data_value[] = "world";
    operation_t operation = {.type = OPERATION_TYPE_MANAGE_DATA,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .manage_data_op = {.data_name_size = 5,
                                                .data_value_size = 5,
                                                .data_name = data_name,
                                                .data_value = data_value}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xbb, 0x1a, 0x45, 0x70, 0x42, 0xcc, 0x57, 0xd4, 0x1b, 0xac, 0x5d,
                             0x88, 0x3a, 0x7,  0x94, 0xe2, 0xc4, 0xd6, 0x1f, 0xe2, 0x4b, 0x78,
                             0x1d, 0x8e, 0x60, 0xfe, 0x39, 0xc2, 0xf1, 0xdb, 0xef, 0x36};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_manage_data_remove_data() {
    uint8_t data_name[] = "hello";
    operation_t operation = {.type = OPERATION_TYPE_MANAGE_DATA,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .manage_data_op = {
                                 .data_name_size = 5,
                                 .data_value_size = 0,
                                 .data_name = data_name,
                             }};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xe7, 0xf7, 0xcd, 0x1,  0xf3, 0x7b, 0xad, 0x9d, 0x34, 0x48, 0x28,
                             0x24, 0xe8, 0xbc, 0x13, 0xfe, 0xde, 0x53, 0xea, 0x2c, 0x4d, 0x2,
                             0x85, 0xf6, 0xf8, 0x45, 0x26, 0xca, 0xbf, 0xe,  0xa6, 0x45};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_account_op),
        cmocka_unit_test(test_payment_op),
        cmocka_unit_test(test_path_payment_strict_receive_op),
        cmocka_unit_test(test_manage_sell_offer_op),
        cmocka_unit_test(test_create_passive_sell_offer_op),
        cmocka_unit_test(test_change_trust_op),
        cmocka_unit_test(test_allow_trust_op),
        cmocka_unit_test(test_account_merge_op),
        cmocka_unit_test(test_inflation_op),
        cmocka_unit_test(test_manage_data_set_data),
        cmocka_unit_test(test_manage_data_remove_data),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}