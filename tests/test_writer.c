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

static void test_set_options_op() {
    uint8_t home_domain[] = "example.com";

    operation_t operation = {
        .type = OPERATION_TYPE_SET_OPTIONS,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .set_options_op = {.inflation_destination_present = true,
                           .inflation_destination = kp2_public,
                           .clear_flags_present = true,
                           .clear_flags = 2,
                           .set_flags_present = true,
                           .set_flags = 4,
                           .master_weight_present = true,
                           .master_weight = 1,
                           .low_threshold_present = true,
                           .low_threshold = 10,
                           .medium_threshold_present = true,
                           .medium_threshold = 20,
                           .high_threshold_present = true,
                           .high_threshold = 30,
                           .home_domain_present = true,
                           .home_domain = home_domain,
                           .home_domain_size = 11,
                           .signer_present = true,
                           .signer = {
                               .key = {.type = SIGNER_KEY_TYPE_ED25519, .ed25519 = kp2_public},
                               .weight = 5,
                           }}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x80, 0x50, 0x34, 0xf7, 0x70, 0x3d, 0xf8, 0x80, 0xe3, 0xd,  0xc3,
                             0xc,  0x1c, 0xf,  0x86, 0x60, 0x26, 0x28, 0xf3, 0xe4, 0x7d, 0x2a,
                             0x96, 0xa9, 0x6,  0x32, 0x11, 0x5c, 0x22, 0x5d, 0x4,  0xa5};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_set_options_op_empty() {
    operation_t operation = {.type = OPERATION_TYPE_SET_OPTIONS,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .set_options_op = {

                             }};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xbe, 0xce, 0x24, 0x7c, 0xf1, 0x1e, 0xc6, 0xaf, 0xa,  0xd9, 0x23,
                             0x84, 0x3,  0xf6, 0x96, 0x43, 0x6,  0x62, 0xc5, 0x18, 0xb2, 0x6,
                             0x6b, 0x6b, 0x53, 0xf1, 0x7c, 0xb4, 0xe6, 0xec, 0xa0, 0x84};

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

static void test_bump_sequence() {
    operation_t operation = {.type = OPERATION_TYPE_BUMP_SEQUENCE,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .bump_sequence_op = {.bump_to = 12345678900001}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xe8, 0x44, 0x64, 0xb,  0x92, 0xa8, 0x2,  0x74, 0x57, 0x10, 0xb8,
                             0x94, 0xf1, 0x40, 0x22, 0x71, 0x4d, 0x6c, 0x74, 0xcf, 0x2c, 0x8b,
                             0xf7, 0xc8, 0x91, 0xc8, 0x8c, 0xd0, 0x24, 0x1a, 0x57, 0xe0};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_manage_buy_offer_op() {
    uint8_t issuer1[] = {0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4,
                         0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3,
                         0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8};
    asset_t asset1 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                      .alpha_num4 = {.asset_code = "USD", .issuer = issuer1}};

    operation_t operation = {.type = OPERATION_TYPE_MANAGE_BUY_OFFER,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .manage_buy_offer_op = {
                                 .selling = {.type = ASSET_TYPE_NATIVE},
                                 .buying = asset1,
                                 .buy_amount = 100000000,
                                 .price = {.n = 1, .d = 1},
                                 .offer_id = 123456,
                             }};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x88, 0xfe, 0x5c, 0xa2, 0xa5, 0x23, 0x79, 0xd7, 0x4e, 0x3b, 0x6f,
                             0x4a, 0xf8, 0x30, 0xc3, 0xa3, 0x5f, 0x3e, 0x33, 0xd9, 0x6f, 0x59,
                             0x7f, 0xc6, 0x7f, 0x1a, 0x75, 0xb1, 0x55, 0xd9, 0xea, 0x18};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_path_payment_strict_send_op() {
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

    operation_t operation = {.type = OPERATION_TYPE_PATH_PAYMENT_STRICT_SEND,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .path_payment_strict_send_op = {
                                 .destination = {.type = KEY_TYPE_ED25519, .ed25519 = kp2_public},
                                 .send_asset = {.type = ASSET_TYPE_NATIVE},
                                 .send_amount = 1000000000,
                                 .dest_asset = asset1,
                                 .dest_min = 2000000000,
                                 .path_len = 2,
                             }};
    memcpy(&operation.path_payment_strict_receive_op.path[0], &asset2, sizeof(asset2));
    memcpy(&operation.path_payment_strict_receive_op.path[1], &asset3, sizeof(asset3));

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x69, 0xba, 0xd9, 0x8f, 0x74, 0x99, 0x4b, 0xcf, 0x8c, 0x49, 0x62,
                             0x10, 0xb5, 0x61, 0xf4, 0x4a, 0x6f, 0x58, 0x4e, 0x2,  0x9c, 0x25,
                             0x8e, 0x42, 0x34, 0xda, 0xf3, 0x25, 0x19, 0xa9, 0x97, 0xd6};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_claim_claimable_balance_op() {
    uint8_t v0[] = {0xda, 0xd,  0x57, 0xda, 0x7d, 0x48, 0x50, 0xe7, 0xfc, 0x10, 0xd2,
                    0xa9, 0xd0, 0xeb, 0xc7, 0x31, 0xf7, 0xaf, 0xb4, 0x5,  0x74, 0xc0,
                    0x33, 0x95, 0xb1, 0x7d, 0x49, 0x14, 0x9b, 0x91, 0xf5, 0xbe};
    operation_t operation = {.type = OPERATION_TYPE_CLAIM_CLAIMABLE_BALANCE,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .claim_claimable_balance_op = {
                                 .balance_id = {.type = CLAIMABLE_BALANCE_ID_TYPE_V0, .v0 = v0}}};
    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xd8, 0x1e, 0xea, 0x50, 0xca, 0x2e, 0xa9, 0xb7, 0x75, 0x92, 0xde,
                             0xf8, 0x5f, 0x3,  0xa8, 0xad, 0xfa, 0x9f, 0xb,  0xf,  0x96, 0xe6,
                             0x45, 0xb7, 0x6e, 0xf8, 0xad, 0x56, 0x8e, 0xad, 0x4e, 0xd6};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_begin_sponsoring_future_reserves() {
    operation_t operation = {.type = OPERATION_TYPE_BEGIN_SPONSORING_FUTURE_RESERVES,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .begin_sponsoring_future_reserves_op = {.sponsored_id = kp2_public}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x8d, 0xd6, 0x13, 0x46, 0xea, 0xe3, 0x8,  0x1f, 0xf,  0xbb, 0x4d,
                             0x83, 0x74, 0xa7, 0x25, 0x88, 0x98, 0xc0, 0x86, 0x63, 0x47, 0x52,
                             0xec, 0x9e, 0xf8, 0x3b, 0x59, 0xe9, 0x43, 0xf8, 0x46, 0xe0};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_end_sponsoring_future_reserves() {
    operation_t operation = {
        .type = OPERATION_TYPE_END_SPONSORING_FUTURE_RESERVES,
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

    uint8_t expect_hash[] = {0xde, 0xc3, 0xd2, 0x16, 0xd8, 0x7,  0xa1, 0x1d, 0x8e, 0xe8, 0x68,
                             0x9e, 0xbc, 0x74, 0x97, 0xeb, 0x87, 0xd9, 0x56, 0x8c, 0x84, 0x7d,
                             0x61, 0xdd, 0x34, 0x2f, 0x97, 0x3b, 0xe1, 0x45, 0xe0, 0x36};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_revoke_account_sponsorship_op() {
    operation_t operation = {
        .type = OPERATION_TYPE_REVOKE_SPONSORSHIP,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .revoke_sponsorship_op = {
            .type = REVOKE_SPONSORSHIP_LEDGER_ENTRY,
            .ledger_key = {.type = ACCOUNT, .account = {.account_id = kp2_public}}}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xb1, 0x60, 0x28, 0x60, 0xba, 0xf6, 0x16, 0xa5, 0xc0, 0x51, 0xee,
                             0xe4, 0x8e, 0xff, 0x8b, 0x18, 0xdd, 0x4d, 0x45, 0xbc, 0xbd, 0xb9,
                             0xaf, 0x23, 0x36, 0x32, 0x3e, 0x9f, 0xd,  0x73, 0x42, 0xef};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_revoke_trustline_sponsorship_op_asset() {
    uint8_t issuer1[] = {0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4,
                         0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3,
                         0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8};
    trust_line_asset_t asset1 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                                 .alpha_num4 = {.asset_code = "USD", .issuer = issuer1}};

    operation_t operation = {
        .type = OPERATION_TYPE_REVOKE_SPONSORSHIP,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .revoke_sponsorship_op = {
            .type = REVOKE_SPONSORSHIP_LEDGER_ENTRY,
            .ledger_key = {.type = TRUSTLINE,
                           .trust_line = {.account_id = kp2_public, .asset = asset1}}}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x1b, 0x4,  0xe3, 0xcd, 0x9f, 0x5d, 0xb5, 0xa4, 0xaa, 0xa3, 0x67,
                             0xf4, 0xbd, 0xc4, 0x65, 0x5f, 0x98, 0x65, 0xfb, 0xdf, 0x4b, 0x68,
                             0x9b, 0xf7, 0x9c, 0x3a, 0x6,  0x9a, 0x1b, 0xf6, 0xad, 0xe8};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_revoke_trustline_sponsorship_op_pool() {
    uint8_t liquidity_pool_id[] = {0xdd, 0x7b, 0x1a, 0xb8, 0x31, 0xc2, 0x73, 0x31, 0xd,  0xdb, 0xec,
                                   0x6f, 0x97, 0x87, 0xa,  0xa8, 0x3c, 0x2f, 0xbd, 0x78, 0xce, 0x22,
                                   0xad, 0xed, 0x37, 0xec, 0xbf, 0x4f, 0x33, 0x80, 0xfa, 0xc7};
    trust_line_asset_t asset1 = {.type = ASSET_TYPE_POOL_SHARE,
                                 .liquidity_pool_id = liquidity_pool_id};

    operation_t operation = {
        .type = OPERATION_TYPE_REVOKE_SPONSORSHIP,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .revoke_sponsorship_op = {
            .type = REVOKE_SPONSORSHIP_LEDGER_ENTRY,
            .ledger_key = {.type = TRUSTLINE,
                           .trust_line = {.account_id = kp2_public, .asset = asset1}}}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xba, 0x61, 0x89, 0x7,  0x11, 0xa7, 0x32, 0xe6, 0x52, 0x5, 0xcc,
                             0xc1, 0x6d, 0xf6, 0x96, 0xfd, 0xa9, 0x23, 0xbd, 0x33, 0xf, 0x7d,
                             0xb0, 0xe2, 0xcd, 0x8d, 0xc3, 0xf2, 0xa8, 0x16, 0x39, 0xb3};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_revoke_offer_sponsorship_op() {
    operation_t operation = {
        .type = OPERATION_TYPE_REVOKE_SPONSORSHIP,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .revoke_sponsorship_op = {
            .type = REVOKE_SPONSORSHIP_LEDGER_ENTRY,
            .ledger_key = {.type = OFFER, .offer = {.seller_id = kp2_public, .offer_id = 123456}}}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x11, 0x1,  0x10, 0x90, 0x98, 0xde, 0x1e, 0xe5, 0xd4, 0x55, 0xe1,
                             0xcc, 0xe2, 0x58, 0xdf, 0x8a, 0xc3, 0x20, 0xe5, 0xf9, 0x6d, 0x74,
                             0xb1, 0xd8, 0xb2, 0x22, 0x7c, 0x84, 0x5e, 0x85, 0xc8, 0xc9};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_revoke_data_sponsorship_op() {
    uint8_t data_name[] = "hello";
    operation_t operation = {
        .type = OPERATION_TYPE_REVOKE_SPONSORSHIP,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .revoke_sponsorship_op = {
            .type = REVOKE_SPONSORSHIP_LEDGER_ENTRY,
            .ledger_key = {
                .type = DATA,
                .data = {.account_id = kp2_public, .data_name_size = 5, .data_name = data_name}}}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x28, 0xaf, 0x88, 0x18, 0xe9, 0xf4, 0x1,  0xf6, 0xa9, 0xfb, 0x48,
                             0x6f, 0xcd, 0xaa, 0x2b, 0x82, 0xe8, 0xec, 0xe1, 0x24, 0x28, 0x72,
                             0x98, 0xeb, 0xee, 0x32, 0x1,  0xcf, 0x1a, 0x98, 0x31, 0x23};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_revoke_claimable_balance_sponsorship_op() {
    uint8_t v0[] = {0xda, 0xd,  0x57, 0xda, 0x7d, 0x48, 0x50, 0xe7, 0xfc, 0x10, 0xd2,
                    0xa9, 0xd0, 0xeb, 0xc7, 0x31, 0xf7, 0xaf, 0xb4, 0x5,  0x74, 0xc0,
                    0x33, 0x95, 0xb1, 0x7d, 0x49, 0x14, 0x9b, 0x91, 0xf5, 0xbe};
    operation_t operation = {
        .type = OPERATION_TYPE_REVOKE_SPONSORSHIP,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .revoke_sponsorship_op = {
            .type = REVOKE_SPONSORSHIP_LEDGER_ENTRY,
            .ledger_key = {.type = CLAIMABLE_BALANCE,
                           .claimable_balance = {
                               .balance_id = {.type = CLAIMABLE_BALANCE_ID_TYPE_V0, .v0 = v0}}}}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xd0, 0x50, 0x35, 0x4f, 0xfc, 0x5d, 0x16, 0x32, 0x50, 0xa,  0x8f,
                             0x71, 0xc,  0xaf, 0x34, 0x32, 0xd8, 0x32, 0xff, 0xc1, 0xaf, 0x6a,
                             0xf5, 0x2b, 0xf4, 0xd7, 0x4c, 0xbd, 0x6,  0x46, 0xf3, 0x73};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_revoke_liquidity_pool_sponsorship_op() {
    uint8_t liquidity_pool_id[] = {0xdd, 0x7b, 0x1a, 0xb8, 0x31, 0xc2, 0x73, 0x31, 0xd,  0xdb, 0xec,
                                   0x6f, 0x97, 0x87, 0xa,  0xa8, 0x3c, 0x2f, 0xbd, 0x78, 0xce, 0x22,
                                   0xad, 0xed, 0x37, 0xec, 0xbf, 0x4f, 0x33, 0x80, 0xfa, 0xc7};
    operation_t operation = {
        .type = OPERATION_TYPE_REVOKE_SPONSORSHIP,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .revoke_sponsorship_op = {
            .type = REVOKE_SPONSORSHIP_LEDGER_ENTRY,
            .ledger_key = {.type = LIQUIDITY_POOL,
                           .liquidity_pool = {.liquidity_pool_id = liquidity_pool_id}}}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x64, 0x38, 0x3c, 0x6f, 0x58, 0xc6, 0x69, 0xe5, 0xed, 0x66, 0x8,
                             0x84, 0x95, 0xda, 0x9a, 0x4c, 0xd3, 0xda, 0xbe, 0x46, 0xd1, 0xdb,
                             0x7f, 0xbd, 0xfb, 0x48, 0xb6, 0xa7, 0xc6, 0x5f, 0xae, 0xf0};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_revoke_signer_sponsorship_op() {
    uint8_t key[] = {0x58, 0x90, 0x92, 0x8,  0x3e, 0x31, 0xdc, 0x53, 0x1a, 0x23, 0x24,
                     0xb8, 0xab, 0xf0, 0xf4, 0xfc, 0x69, 0x3f, 0x65, 0x8a, 0x55, 0x92,
                     0xe0, 0xa5, 0x50, 0x2,  0xa9, 0xe3, 0x42, 0xb1, 0x97, 0x55};
    signer_key_t signer_key = {.type = SIGNER_KEY_TYPE_ED25519, .ed25519 = key};
    operation_t operation = {
        .type = OPERATION_TYPE_REVOKE_SPONSORSHIP,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .revoke_sponsorship_op = {.type = REVOKE_SPONSORSHIP_SIGNER,
                                  .signer = {.account_id = kp2_public, .signer_key = signer_key}}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x51, 0xc9, 0xaa, 0xc5, 0x38, 0x6a, 0xa2, 0xe1, 0xaf, 0x71, 0x47,
                             0xb0, 0xcb, 0x27, 0x75, 0xd6, 0xeb, 0xf6, 0xd7, 0x1c, 0xd5, 0xaa,
                             0x71, 0x7b, 0x3f, 0x15, 0xee, 0xbe, 0xf3, 0x8b, 0x51, 0x7c};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_clawback_op() {
    uint8_t issuer1[] = {0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4,
                         0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3,
                         0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8};
    asset_t asset1 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                      .alpha_num4 = {.asset_code = "USD", .issuer = issuer1}};
    muxed_account_t from = {.type = KEY_TYPE_ED25519, .ed25519 = kp2_public};
    operation_t operation = {.type = OPERATION_TYPE_CLAWBACK,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .clawback_op = {.asset = asset1, .from = from, .amount = 100000000}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xe2, 0x45, 0xda, 0x77, 0x17, 0x3d, 0xc5, 0x9,  0xaa, 0x36, 0x15,
                             0x19, 0x22, 0x65, 0xfd, 0x4b, 0xe2, 0xf8, 0x6b, 0x1a, 0x9a, 0xe2,
                             0x94, 0x6e, 0x21, 0xff, 0x1b, 0x42, 0x23, 0x73, 0x48, 0x4f};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_clawback_claimable_balance_op() {
    uint8_t v0[] = {0xda, 0xd,  0x57, 0xda, 0x7d, 0x48, 0x50, 0xe7, 0xfc, 0x10, 0xd2,
                    0xa9, 0xd0, 0xeb, 0xc7, 0x31, 0xf7, 0xaf, 0xb4, 0x5,  0x74, 0xc0,
                    0x33, 0x95, 0xb1, 0x7d, 0x49, 0x14, 0x9b, 0x91, 0xf5, 0xbe};
    operation_t operation = {.type = OPERATION_TYPE_CLAWBACK_CLAIMABLE_BALANCE,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .clawback_claimable_balance_op = {
                                 .balance_id = {.type = CLAIMABLE_BALANCE_ID_TYPE_V0, .v0 = v0}}};
    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x8,  0x16, 0x59, 0x8f, 0x5f, 0xe0, 0xca, 0xbb, 0x7d, 0x4d, 0xb9,
                             0x4a, 0x31, 0x82, 0x2a, 0x93, 0x85, 0xa,  0x2,  0x6c, 0x1c, 0xfa,
                             0xa5, 0x39, 0xe2, 0x87, 0xc3, 0x5,  0xcd, 0x21, 0x32, 0x1c};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_set_trust_line_flags_op() {
    uint8_t issuer1[] = {0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4,
                         0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3,
                         0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8};
    asset_t asset1 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                      .alpha_num4 = {.asset_code = "USD", .issuer = issuer1}};
    operation_t operation = {
        .type = OPERATION_TYPE_SET_TRUST_LINE_FLAGS,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .set_trust_line_flags_op = {.asset = asset1,
                                    .trustor = kp2_public,
                                    .clear_flags = AUTHORIZED_FLAG,
                                    .set_flags = TRUSTLINE_CLAWBACK_ENABLED_FLAG}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xb4, 0x50, 0x94, 0x53, 0x6,  0xed, 0x8f, 0x27, 0x43, 0x6f, 0xc3,
                             0xa6, 0x28, 0xc1, 0xfe, 0xda, 0x7b, 0xc,  0xef, 0xeb, 0xc7, 0x50,
                             0x3f, 0x34, 0x64, 0x84, 0x69, 0x2a, 0xe1, 0xc5, 0xdb, 0xc5};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_liquidity_pool_deposit_op() {
    uint8_t liquidity_pool_id[] = {0x61, 0x90, 0x9,  0x98, 0xf1, 0x6a, 0x79, 0x7e, 0x1c, 0x1d, 0xbb,
                                   0x2e, 0xb2, 0x1a, 0x1,  0x65, 0x7d, 0xa5, 0x8e, 0x6c, 0xc2, 0xf2,
                                   0xba, 0xdc, 0x4c, 0x1e, 0xf7, 0x90, 0xf1, 0x7a, 0x22, 0xca};
    operation_t operation = {.type = OPERATION_TYPE_LIQUIDITY_POOL_DEPOSIT,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .liquidity_pool_deposit_op = {.liquidity_pool_id = liquidity_pool_id,
                                                           .max_amount_a = 100000000,
                                                           .max_amount_b = 200000000,
                                                           .min_price = {.n = 9, .d = 20},
                                                           .max_price = {.n = 11, .d = 20}}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x2d, 0x0,  0x62, 0xcc, 0xe1, 0x14, 0xb7, 0xd6, 0x86, 0xd5, 0x70,
                             0xd9, 0xad, 0xd8, 0x63, 0x72, 0xcf, 0x42, 0xfe, 0x3d, 0x61, 0x8d,
                             0xe4, 0xd7, 0x74, 0x50, 0xe4, 0x34, 0xe8, 0x47, 0x37, 0xa0};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_liquidity_pool_withdraw_op() {
    uint8_t liquidity_pool_id[] = {0x61, 0x90, 0x9,  0x98, 0xf1, 0x6a, 0x79, 0x7e, 0x1c, 0x1d, 0xbb,
                                   0x2e, 0xb2, 0x1a, 0x1,  0x65, 0x7d, 0xa5, 0x8e, 0x6c, 0xc2, 0xf2,
                                   0xba, 0xdc, 0x4c, 0x1e, 0xf7, 0x90, 0xf1, 0x7a, 0x22, 0xca};
    operation_t operation = {.type = OPERATION_TYPE_LIQUIDITY_POOL_WITHDRAW,
                             .source_account_present = true,
                             .source_account =
                                 {
                                     .type = KEY_TYPE_ED25519,
                                     .ed25519 = kp1_public,
                                 },
                             .liquidity_pool_withdraw_op = {.liquidity_pool_id = liquidity_pool_id,
                                                            .min_amount_a = 100000000,
                                                            .min_amount_b = 200000000,
                                                            .amount = 50000000}};

    sha256_init(&sha256_ctx);
    write_operation(&operation, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x69, 0xe0, 0xa8, 0x32, 0xb6, 0x9b, 0x89, 0xdc, 0x2c, 0xcc, 0x2b,
                             0xa3, 0xb5, 0x91, 0x41, 0x4f, 0xae, 0xfa, 0x67, 0xb5, 0x90, 0xc5,
                             0x81, 0xd9, 0xfc, 0xa7, 0xa2, 0x9a, 0x9a, 0xdd, 0x97, 0xa5};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_memo_none() {
    memo_t memo = {.type = MEMO_NONE};
    sha256_init(&sha256_ctx);
    write_transaction_memo(&memo, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xdf, 0x3f, 0x61, 0x98, 0x4,  0xa9, 0x2f, 0xdb, 0x40, 0x57, 0x19,
                             0x2d, 0xc4, 0x3d, 0xd7, 0x48, 0xea, 0x77, 0x8a, 0xdc, 0x52, 0xbc,
                             0x49, 0x8c, 0xe8, 0x5,  0x24, 0xc0, 0x14, 0xb8, 0x11, 0x19};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_memo_text() {
    uint8_t text[] = "hello";
    memo_t memo = {.type = MEMO_TEXT, .text = {.text_size = 5, .text = text}};
    sha256_init(&sha256_ctx);
    write_transaction_memo(&memo, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x1d, 0xc4, 0xd6, 0x10, 0x47, 0x3d, 0xbb, 0xef, 0xba, 0x28, 0x96,
                             0x7c, 0x42, 0x84, 0xbb, 0x92, 0xf9, 0x5a, 0x88, 0xae, 0x62, 0xc6,
                             0x6,  0xb3, 0xe0, 0xb0, 0x3a, 0xc2, 0xa7, 0xe1, 0x6a, 0xc1};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_memo_id() {
    memo_t memo = {.type = MEMO_ID, .id = 123456};
    sha256_init(&sha256_ctx);
    write_transaction_memo(&memo, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xd0, 0xe1, 0x38, 0x6,  0xc9, 0x4a, 0x9a, 0xa6, 0xc,  0xe2, 0xc,
                             0x96, 0x6d, 0x47, 0xe9, 0x1e, 0x99, 0x25, 0xc6, 0xa1, 0x60, 0x3c,
                             0xfd, 0x4a, 0x45, 0x96, 0x85, 0xe5, 0xd4, 0xdd, 0xfe, 0xe9};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_memo_hash() {
    uint8_t data[] = {0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
                      0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
                      0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61};

    memo_t memo = {.type = MEMO_HASH, .hash = data};
    sha256_init(&sha256_ctx);
    write_transaction_memo(&memo, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x38, 0x1e, 0x49, 0x32, 0xb1, 0x1c, 0x13, 0x4e, 0x84, 0x57, 0x76,
                             0x6d, 0x64, 0xac, 0x19, 0x20, 0x56, 0x24, 0xc9, 0x93, 0xb7, 0x2f,
                             0x3,  0x4c, 0x10, 0xa8, 0xff, 0xa1, 0xb9, 0x45, 0xed, 0xc3};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_memo_return_hash() {
    uint8_t data[] = {0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
                      0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
                      0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61};

    memo_t memo = {.type = MEMO_RETURN, .hash = data};
    sha256_init(&sha256_ctx);
    write_transaction_memo(&memo, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x9c, 0x9a, 0x1a, 0x36, 0xba, 0x7b, 0xe1, 0x2b, 0x90, 0xb8, 0x4d,
                             0x3a, 0x5b, 0x2e, 0x29, 0x63, 0x40, 0x25, 0x4e, 0xc2, 0xc5, 0x1e,
                             0x9c, 0x4b, 0xca, 0xf8, 0x1c, 0x39, 0xf0, 0x43, 0xf1, 0x44};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_signer_key_ed25519_public_key() {
    uint8_t key[] = {0x62, 0x5f, 0x3d, 0x59, 0xc3, 0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda,
                     0x5e, 0x8,  0xc5, 0xd6, 0xe4, 0xbd, 0xf0, 0xd1, 0x50, 0x3a, 0xb9,
                     0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb, 0x9,  0x1e, 0x5d, 0xa1};
    signer_key_t signer_key = {.type = SIGNER_KEY_TYPE_ED25519, .ed25519 = key};
    sha256_init(&sha256_ctx);
    write_signer_key(&signer_key, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x87, 0xb,  0xb5, 0xe3, 0x1e, 0x14, 0xfc, 0x3e, 0x29, 0xbc, 0xaf,
                             0x6f, 0x72, 0x49, 0x80, 0xbd, 0x43, 0xe8, 0x9c, 0x53, 0xb2, 0x55,
                             0xba, 0x6,  0xbc, 0xee, 0x2d, 0x2c, 0x25, 0x4b, 0x71, 0x51};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_signer_key_pre_auth_tx() {
    uint8_t key[] = {0x62, 0x5f, 0x3d, 0x59, 0xc3, 0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda,
                     0x5e, 0x8,  0xc5, 0xd6, 0xe4, 0xbd, 0xf0, 0xd1, 0x50, 0x3a, 0xb9,
                     0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb, 0x9,  0x1e, 0x5d, 0xa1};
    signer_key_t signer_key = {.type = SIGNER_KEY_TYPE_PRE_AUTH_TX, .pre_auth_tx = key};
    sha256_init(&sha256_ctx);
    write_signer_key(&signer_key, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x16, 0xee, 0xfe, 0x2b, 0x56, 0x80, 0xe4, 0x1f, 0x86, 0x9d, 0x2,
                             0x4a, 0x10, 0x99, 0xe6, 0xc8, 0x3d, 0xe7, 0x4c, 0xa2, 0xf7, 0x98,
                             0x51, 0x3f, 0x31, 0xf2, 0xb8, 0x74, 0x35, 0x5f, 0x52, 0x42};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_signer_key_hash_x() {
    uint8_t key[] = {0x62, 0x5f, 0x3d, 0x59, 0xc3, 0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda,
                     0x5e, 0x8,  0xc5, 0xd6, 0xe4, 0xbd, 0xf0, 0xd1, 0x50, 0x3a, 0xb9,
                     0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb, 0x9,  0x1e, 0x5d, 0xa1};
    signer_key_t signer_key = {.type = SIGNER_KEY_TYPE_HASH_X, .hash_x = key};
    sha256_init(&sha256_ctx);
    write_signer_key(&signer_key, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xc6, 0x34, 0x3e, 0x56, 0x12, 0x79, 0xaa, 0xd3, 0x52, 0x56, 0x4b,
                             0xdd, 0x6a, 0x40, 0x1a, 0x69, 0xa3, 0x89, 0x27, 0x51, 0x81, 0x74,
                             0x1f, 0xb8, 0x3b, 0x3f, 0xe2, 0xb3, 0x54, 0x8,  0xd2, 0x95};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_signer_key_ed25519_signed_payload() {
    uint8_t key[] = {0x62, 0x5f, 0x3d, 0x59, 0xc3, 0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda,
                     0x5e, 0x8,  0xc5, 0xd6, 0xe4, 0xbd, 0xf0, 0xd1, 0x50, 0x3a, 0xb9,
                     0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb, 0x9,  0x1e, 0x5d, 0xa1};
    uint8_t payload[] = {0x68, 0x65, 0x79};

    signer_key_t signer_key = {
        .type = SIGNER_KEY_TYPE_ED25519_SIGNED_PAYLOAD,
        .ed25519_signed_payload = {.ed25519 = key, .payload = payload, .payload_len = 3}};
    sha256_init(&sha256_ctx);
    write_signer_key(&signer_key, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xca, 0x83, 0x64, 0xc9, 0x5e, 0xe,  0x4f, 0x70, 0xa2, 0x8d, 0x92,
                             0xbd, 0x3f, 0x6c, 0x90, 0xa,  0x8b, 0x84, 0x65, 0xe0, 0xa2, 0x90,
                             0x77, 0xab, 0xc6, 0x60, 0x77, 0xf7, 0x60, 0x24, 0xb4, 0x5f};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_preconditions_v2() {
    preconditions_t preconditions = {
        .time_bounds_present = true,
        .ledger_bounds_present = true,
        .min_seq_num_present = true,
        .time_bounds = {.min_time = 1649237469, .max_time = 1649238469},
        .ledger_bounds = {.min_ledger = 40351800, .max_ledger = 40352000},
        .min_seq_num = 103420918407103888,
        .min_seq_ledger_gap = 30,
        .min_seq_age = 1649239999,
        .extra_signers_len = 2,
    };
    signer_key_t signer_key0 = {.type = SIGNER_KEY_TYPE_ED25519, .ed25519 = kp1_public};
    signer_key_t signer_key1 = {.type = SIGNER_KEY_TYPE_ED25519, .ed25519 = kp2_public};
    memcpy(&preconditions.extra_signers[0], &signer_key0, sizeof(signer_key0));
    memcpy(&preconditions.extra_signers[1], &signer_key1, sizeof(signer_key1));

    sha256_init(&sha256_ctx);
    write_transaction_preconditions(&preconditions, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xbb, 0xcc, 0x9e, 0xe9, 0xac, 0x77, 0xa4, 0x94, 0x69, 0xae, 0x4,
                             0xbe, 0xa6, 0x5d, 0x4d, 0x91, 0xc8, 0x76, 0x76, 0x95, 0x73, 0x4e,
                             0x29, 0x16, 0xbc, 0x4f, 0xc,  0xbd, 0x5f, 0x5b, 0xfb, 0x1b};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_preconditions_v0() {
    preconditions_t preconditions = {
        .time_bounds_present = false,
        .ledger_bounds_present = false,
        .min_seq_num_present = false,
        .time_bounds = {.min_time = 1649237469, .max_time = 1649238469},
        .ledger_bounds = {.min_ledger = 40351800, .max_ledger = 40352000},
        .min_seq_num = 103420918407103888,
        .min_seq_ledger_gap = 30,
        .min_seq_age = 1649239999,
        .extra_signers_len = 2,
    };
    signer_key_t signer_key0 = {.type = SIGNER_KEY_TYPE_ED25519, .ed25519 = kp1_public};
    signer_key_t signer_key1 = {.type = SIGNER_KEY_TYPE_ED25519, .ed25519 = kp2_public};
    memcpy(&preconditions.extra_signers[0], &signer_key0, sizeof(signer_key0));
    memcpy(&preconditions.extra_signers[1], &signer_key1, sizeof(signer_key1));

    sha256_init(&sha256_ctx);
    write_transaction_preconditions(&preconditions, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xdf, 0x3f, 0x61, 0x98, 0x4,  0xa9, 0x2f, 0xdb, 0x40, 0x57, 0x19,
                             0x2d, 0xc4, 0x3d, 0xd7, 0x48, 0xea, 0x77, 0x8a, 0xdc, 0x52, 0xbc,
                             0x49, 0x8c, 0xe8, 0x5,  0x24, 0xc0, 0x14, 0xb8, 0x11, 0x19};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_preconditions_none() {
    preconditions_t preconditions = {
        .time_bounds_present = false,
        .ledger_bounds_present = false,
        .min_seq_num_present = false,

    };
    signer_key_t signer_key0 = {.type = SIGNER_KEY_TYPE_ED25519, .ed25519 = kp1_public};
    signer_key_t signer_key1 = {.type = SIGNER_KEY_TYPE_ED25519, .ed25519 = kp2_public};
    memcpy(&preconditions.extra_signers[0], &signer_key0, sizeof(signer_key0));
    memcpy(&preconditions.extra_signers[1], &signer_key1, sizeof(signer_key1));

    sha256_init(&sha256_ctx);
    write_transaction_preconditions(&preconditions, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0xdf, 0x3f, 0x61, 0x98, 0x4,  0xa9, 0x2f, 0xdb, 0x40, 0x57, 0x19,
                             0x2d, 0xc4, 0x3d, 0xd7, 0x48, 0xea, 0x77, 0x8a, 0xdc, 0x52, 0xbc,
                             0x49, 0x8c, 0xe8, 0x5,  0x24, 0xc0, 0x14, 0xb8, 0x11, 0x19};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_preconditions_time() {
    preconditions_t preconditions = {
        .time_bounds_present = true,
        .time_bounds = {.min_time = 1649237469, .max_time = 1649238469},
    };
    signer_key_t signer_key0 = {.type = SIGNER_KEY_TYPE_ED25519, .ed25519 = kp1_public};
    signer_key_t signer_key1 = {.type = SIGNER_KEY_TYPE_ED25519, .ed25519 = kp2_public};
    memcpy(&preconditions.extra_signers[0], &signer_key0, sizeof(signer_key0));
    memcpy(&preconditions.extra_signers[1], &signer_key1, sizeof(signer_key1));

    sha256_init(&sha256_ctx);
    write_transaction_preconditions(&preconditions, sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x6f, 0x33, 0xe,  0xa4, 0x4,  0xc7, 0xe0, 0x0,  0xd,  0x57, 0x7a,
                             0x1c, 0xec, 0x51, 0xa4, 0xbb, 0x50, 0xd0, 0x42, 0x3,  0xb0, 0x49,
                             0xdf, 0x6d, 0x2b, 0x57, 0x9d, 0x4c, 0x25, 0x30, 0xf5, 0xb0};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_transaction_details() {
    operation_t operation1 = {
        .type = OPERATION_TYPE_PAYMENT,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .payment_op = {.destination = {.type = KEY_TYPE_ED25519, .ed25519 = kp2_public},
                       .amount = 50000000000,
                       .asset = {.type = ASSET_TYPE_NATIVE}}};
    operation_t operation2 = {
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

    transaction_details_t transaction = {
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .sequence_number = 1234567890101010,
        .fee = 200,
        .memo = {.type = MEMO_ID, .id = 123456},
        .cond =
            {
                .time_bounds_present = true,
                .time_bounds = {.min_time = 1649237469, .max_time = 1649238469},
            },
        .operations_count = 2};

    sha256_init(&sha256_ctx);
    write_transaction_details(&transaction, sha256_update_f);
    write_operation(&operation1, sha256_update_f);
    write_operation(&operation2, sha256_update_f);
    write_transaction_ext(sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x79, 0xc8, 0xa8, 0xec, 0x28, 0x91, 0x22, 0xe6, 0x50, 0xe,  0x23,
                             0x5f, 0xf6, 0xc,  0x8c, 0x6a, 0x4a, 0x67, 0x14, 0x46, 0xde, 0x69,
                             0x12, 0xb0, 0x1d, 0xf,  0x53, 0xca, 0xe5, 0x2,  0x79, 0xd5};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

static void test_fee_bump_transaction_details() {
    operation_t operation1 = {
        .type = OPERATION_TYPE_PAYMENT,
        .source_account_present = true,
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .payment_op = {.destination = {.type = KEY_TYPE_ED25519, .ed25519 = kp2_public},
                       .amount = 50000000000,
                       .asset = {.type = ASSET_TYPE_NATIVE}}};
    operation_t operation2 = {
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

    transaction_details_t transaction = {
        .source_account =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .sequence_number = 1234567890101010,
        .fee = 200,
        .memo = {.type = MEMO_ID, .id = 123456},
        .cond =
            {
                .time_bounds_present = true,
                .time_bounds = {.min_time = 1649237469, .max_time = 1649238469},
            },
        .operations_count = 2};

    fee_bump_transaction_details_t fee_bump_transaction = {
        .fee_source =
            {
                .type = KEY_TYPE_ED25519,
                .ed25519 = kp1_public,
            },
        .fee = 900,
    };

    sha256_init(&sha256_ctx);
    write_fee_bump_transaction_details(&fee_bump_transaction, sha256_update_f);
    write_transaction_envelope_type(ENVELOPE_TYPE_TX, sha256_update_f);
    write_transaction_details(&transaction, sha256_update_f);
    write_operation(&operation1, sha256_update_f);
    write_operation(&operation2, sha256_update_f);
    write_transaction_ext(sha256_update_f);
    write_decorated_signature_len(2, sha256_update_f);
    decorated_signature_t decorated_signature1 = {
        .signature_hint = {0x9, 0x1e, 0x5d, 0xa1},
        .signature_size = 64,
        .signature = {0xf1, 0x6a, 0x4,  0xd3, 0xc6, 0xb2, 0x4c, 0x28, 0x0,  0x45, 0x17, 0xcb, 0x39,
                      0x42, 0x6b, 0x8,  0x17, 0xa0, 0xf5, 0xe0, 0x14, 0xd6, 0x9a, 0xa5, 0x5a, 0x68,
                      0xc0, 0x4c, 0xdb, 0xb0, 0x9,  0xca, 0x45, 0xad, 0xc3, 0xa9, 0x3a, 0x1e, 0xab,
                      0x5c, 0x1d, 0xf9, 0x45, 0xdf, 0x96, 0xbd, 0xfa, 0x2b, 0xa,  0xcb, 0x45, 0x8f,
                      0x88, 0xfe, 0xd6, 0x4b, 0x79, 0xc6, 0x79, 0xbf, 0x9f, 0xba, 0x8,  0x2}};
    decorated_signature_t decorated_signature2 = {
        .signature_hint = {0x42, 0xb1, 0x97, 0x55},
        .signature_size = 64,
        .signature = {0x23, 0xc8, 0x93, 0xe1, 0xe8, 0x5,  0xe0, 0x4b, 0x8e, 0x5e, 0xad, 0x8,  0xf,
                      0x20, 0xaf, 0xa,  0x73, 0xaf, 0x78, 0xc2, 0xc,  0x6b, 0x2c, 0xa4, 0xb2, 0xbe,
                      0xe4, 0x44, 0x8b, 0xd2, 0xc0, 0x51, 0x55, 0x83, 0xa4, 0x26, 0xcb, 0xd6, 0xb0,
                      0xc8, 0x49, 0x48, 0x8b, 0x82, 0xf6, 0xe2, 0x6e, 0xca, 0xe9, 0xbb, 0xb7, 0x3f,
                      0xcf, 0xcd, 0x44, 0x98, 0xdb, 0x12, 0x5b, 0x52, 0x4d, 0x6c, 0x8c, 0x2}};
    write_decorated_signature(&decorated_signature1, sha256_update_f);
    write_decorated_signature(&decorated_signature2, sha256_update_f);
    write_fee_bump_transaction_ext(sha256_update_f);
    sha256_final(&sha256_ctx, hash);

    uint8_t expect_hash[] = {0x8c, 0x7,  0xdf, 0x77, 0x2a, 0x19, 0x19, 0x3e, 0xd6, 0x64, 0x4a,
                             0x5b, 0xed, 0xb7, 0xaa, 0x7,  0xf3, 0x5c, 0x23, 0xc3, 0x5d, 0x97,
                             0x4e, 0x12, 0xd6, 0x14, 0x35, 0x41, 0x7e, 0x13, 0xb,  0x21};

    assert_memory_equal(expect_hash, hash, sizeof(hash));
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_account_op),
        cmocka_unit_test(test_payment_op),
        cmocka_unit_test(test_path_payment_strict_receive_op),
        cmocka_unit_test(test_manage_sell_offer_op),
        cmocka_unit_test(test_create_passive_sell_offer_op),
        cmocka_unit_test(test_set_options_op),
        cmocka_unit_test(test_set_options_op_empty),
        cmocka_unit_test(test_change_trust_op),
        cmocka_unit_test(test_allow_trust_op),
        cmocka_unit_test(test_account_merge_op),
        cmocka_unit_test(test_inflation_op),
        cmocka_unit_test(test_manage_data_set_data),
        cmocka_unit_test(test_manage_data_remove_data),
        cmocka_unit_test(test_bump_sequence),
        cmocka_unit_test(test_manage_buy_offer_op),
        cmocka_unit_test(test_path_payment_strict_send_op),
        cmocka_unit_test(test_claim_claimable_balance_op),
        cmocka_unit_test(test_begin_sponsoring_future_reserves),
        cmocka_unit_test(test_end_sponsoring_future_reserves),
        cmocka_unit_test(test_revoke_account_sponsorship_op),
        cmocka_unit_test(test_revoke_trustline_sponsorship_op_asset),
        cmocka_unit_test(test_revoke_trustline_sponsorship_op_pool),
        cmocka_unit_test(test_revoke_offer_sponsorship_op),
        cmocka_unit_test(test_revoke_data_sponsorship_op),
        cmocka_unit_test(test_revoke_claimable_balance_sponsorship_op),
        cmocka_unit_test(test_revoke_liquidity_pool_sponsorship_op),
        cmocka_unit_test(test_revoke_signer_sponsorship_op),
        cmocka_unit_test(test_clawback_op),
        cmocka_unit_test(test_clawback_claimable_balance_op),
        cmocka_unit_test(test_set_trust_line_flags_op),
        cmocka_unit_test(test_liquidity_pool_deposit_op),
        cmocka_unit_test(test_liquidity_pool_withdraw_op),
        cmocka_unit_test(test_memo_none),
        cmocka_unit_test(test_memo_text),
        cmocka_unit_test(test_memo_id),
        cmocka_unit_test(test_memo_hash),
        cmocka_unit_test(test_memo_return_hash),
        cmocka_unit_test(test_signer_key_ed25519_public_key),
        cmocka_unit_test(test_signer_key_pre_auth_tx),
        cmocka_unit_test(test_signer_key_hash_x),
        cmocka_unit_test(test_signer_key_ed25519_signed_payload),
        cmocka_unit_test(test_preconditions_v2),
        cmocka_unit_test(test_preconditions_none),
        cmocka_unit_test(test_preconditions_time),
        cmocka_unit_test(test_transaction_details),
        cmocka_unit_test(test_fee_bump_transaction_details),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
