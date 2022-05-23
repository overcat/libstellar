#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <cmocka.h>

#include "../src/types.h"
#include "../src/utils.h"
#include "../src/reader.h"

uint8_t kp1_public[] = {0x62, 0x5f, 0x3d, 0x59, 0xc3, 0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda,
                        0x5e, 0x8,  0xc5, 0xd6, 0xe4, 0xbd, 0xf0, 0xd1, 0x50, 0x3a, 0xb9,
                        0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb, 0x9,  0x1e, 0x5d, 0xa1};
uint8_t kp2_public[] = {0xb4, 0x69, 0xf8, 0x27, 0xc2, 0x68, 0xa1, 0xfe, 0x55, 0x2,  0xaf,
                        0x55, 0x87, 0x1,  0x11, 0x16, 0x23, 0xe3, 0xbf, 0xf8, 0x81, 0x74,
                        0xb3, 0xb0, 0x6d, 0x56, 0x48, 0x8c, 0xc5, 0x2e, 0xfe, 0xb8};

static void test_create_account_op() {
    uint8_t data[] = {0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x62, 0x5f, 0x3d, 0x59, 0xc3,
                      0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda, 0x5e, 0x8,  0xc5, 0xd6, 0xe4, 0xbd, 0xf0,
                      0xd1, 0x50, 0x3a, 0xb9, 0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb, 0x9,  0x1e, 0x5d,
                      0xa1, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xb4, 0x69, 0xf8, 0x27,
                      0xc2, 0x68, 0xa1, 0xfe, 0x55, 0x2,  0xaf, 0x55, 0x87, 0x1,  0x11, 0x16, 0x23,
                      0xe3, 0xbf, 0xf8, 0x81, 0x74, 0xb3, 0xb0, 0x6d, 0x56, 0x48, 0x8c, 0xc5, 0x2e,
                      0xfe, 0xb8, 0x0,  0x0,  0x0,  0x2,  0xdf, 0xdc, 0x1c, 0x34};

    buffer_t buffer = {.offset = 0, .size = sizeof(data), .ptr = data};
    operation_t operation;
    assert_true(read_operation(&buffer, &operation));
    assert_int_equal(buffer.offset, buffer.size);

    assert_true(operation.source_account_present);
    assert_int_equal(operation.source_account.type, KEY_TYPE_ED25519);
    assert_memory_equal(operation.source_account.ed25519, kp1_public, sizeof(kp1_public));

    assert_int_equal(operation.type, OPERATION_TYPE_CREATE_ACCOUNT);
    assert_int_equal(operation.create_account_op.starting_balance, 12345678900);
    assert_memory_equal(operation.create_account_op.destination, kp2_public, sizeof(kp2_public));
}

static void test_payment_op() {
    uint8_t data[] = {0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x62, 0x5f, 0x3d, 0x59,
                      0xc3, 0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda, 0x5e, 0x8,  0xc5, 0xd6, 0xe4,
                      0xbd, 0xf0, 0xd1, 0x50, 0x3a, 0xb9, 0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb,
                      0x9,  0x1e, 0x5d, 0xa1, 0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,
                      0xb4, 0x69, 0xf8, 0x27, 0xc2, 0x68, 0xa1, 0xfe, 0x55, 0x2,  0xaf, 0x55,
                      0x87, 0x1,  0x11, 0x16, 0x23, 0xe3, 0xbf, 0xf8, 0x81, 0x74, 0xb3, 0xb0,
                      0x6d, 0x56, 0x48, 0x8c, 0xc5, 0x2e, 0xfe, 0xb8, 0x0,  0x0,  0x0,  0x0,
                      0x0,  0x0,  0x0,  0x17, 0x48, 0x76, 0xe8, 0x0};

    buffer_t buffer = {.offset = 0, .size = sizeof(data), .ptr = data};
    operation_t operation;
    assert_true(read_operation(&buffer, &operation));
    assert_int_equal(buffer.offset, buffer.size);

    assert_true(operation.source_account_present);
    assert_int_equal(operation.source_account.type, KEY_TYPE_ED25519);
    assert_memory_equal(operation.source_account.ed25519, kp1_public, sizeof(kp1_public));

    assert_int_equal(operation.type, OPERATION_TYPE_PAYMENT);
    assert_int_equal(operation.payment_op.amount, 100000000000);
    assert_memory_equal(operation.payment_op.destination.ed25519, kp2_public, sizeof(kp2_public));
    assert_int_equal(operation.payment_op.destination.type, KEY_TYPE_ED25519);
    assert_int_equal(operation.payment_op.asset.type, ASSET_TYPE_NATIVE);
}

static void test_path_payment_strict_receive_op() {
    uint8_t data[] = {
        0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x62, 0x5f, 0x3d, 0x59, 0xc3, 0xf8, 0x9e,
        0x59, 0x1a, 0x6,  0xda, 0x5e, 0x8,  0xc5, 0xd6, 0xe4, 0xbd, 0xf0, 0xd1, 0x50, 0x3a, 0xb9,
        0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb, 0x9,  0x1e, 0x5d, 0xa1, 0x0,  0x0,  0x0,  0x2,  0x0,
        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x3b, 0x9a, 0xca, 0x0,  0x0,  0x0,  0x0,  0x0,
        0xb4, 0x69, 0xf8, 0x27, 0xc2, 0x68, 0xa1, 0xfe, 0x55, 0x2,  0xaf, 0x55, 0x87, 0x1,  0x11,
        0x16, 0x23, 0xe3, 0xbf, 0xf8, 0x81, 0x74, 0xb3, 0xb0, 0x6d, 0x56, 0x48, 0x8c, 0xc5, 0x2e,
        0xfe, 0xb8, 0x0,  0x0,  0x0,  0x1,  0x55, 0x53, 0x44, 0x0,  0x0,  0x0,  0x0,  0x0,  0x9b,
        0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4, 0xf7, 0x43, 0x20, 0x71, 0x10,
        0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3, 0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59,
        0xd8, 0x0,  0x0,  0x0,  0x0,  0x77, 0x35, 0x94, 0x0,  0x0,  0x0,  0x0,  0x2,  0x0,  0x0,
        0x0,  0x2,  0x43, 0x41, 0x54, 0x43, 0x4f, 0x49, 0x4e, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
        0x0,  0x0,  0x0,  0xd3, 0x52, 0x8c, 0xdd, 0x70, 0xad, 0xd7, 0xe2, 0xc7, 0xf,  0xb8, 0xc3,
        0x4c, 0xe6, 0x29, 0x7b, 0xf1, 0xc6, 0x29, 0x20, 0xe8, 0x42, 0x8c, 0x8b, 0xd4, 0x96, 0xd4,
        0x39, 0xcd, 0x3e, 0x13, 0x63, 0x0,  0x0,  0x0,  0x2,  0x50, 0x41, 0x4e, 0x44, 0x41, 0x0,
        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0xd3, 0x52, 0x8c, 0xdd, 0x70,
        0xad, 0xd7, 0xe2, 0xc7, 0xf,  0xb8, 0xc3, 0x4c, 0xe6, 0x29, 0x7b, 0xf1, 0xc6, 0x29, 0x20,
        0xe8, 0x42, 0x8c, 0x8b, 0xd4, 0x96, 0xd4, 0x39, 0xcd, 0x3e, 0x13, 0x63};

    buffer_t buffer = {.offset = 0, .size = sizeof(data), .ptr = data};
    operation_t operation;
    assert_true(read_operation(&buffer, &operation));
    assert_int_equal(buffer.offset, buffer.size);

    assert_true(operation.source_account_present);
    assert_int_equal(operation.source_account.type, KEY_TYPE_ED25519);
    assert_memory_equal(operation.source_account.ed25519, kp1_public, sizeof(kp1_public));

    assert_int_equal(operation.type, OPERATION_TYPE_PATH_PAYMENT_STRICT_RECEIVE);
    assert_memory_equal(operation.path_payment_strict_receive_op.destination.ed25519,
                        kp2_public,
                        sizeof(kp2_public));
    assert_int_equal(operation.path_payment_strict_receive_op.destination.type, KEY_TYPE_ED25519);
    assert_int_equal(operation.path_payment_strict_receive_op.send_asset.type, ASSET_TYPE_NATIVE);
    assert_int_equal(operation.path_payment_strict_receive_op.send_max, 1000000000);
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
    assert_int_equal(operation.path_payment_strict_receive_op.dest_asset.type, asset1.type);
    assert_string_equal(operation.path_payment_strict_receive_op.dest_asset.alpha_num4.asset_code,
                        asset1.alpha_num4.asset_code);
    assert_memory_equal(operation.path_payment_strict_receive_op.dest_asset.alpha_num4.issuer,
                        asset1.alpha_num4.issuer,
                        sizeof(asset1.alpha_num4.issuer));
    assert_int_equal(operation.path_payment_strict_receive_op.dest_amount, 2000000000);
    assert_int_equal(operation.path_payment_strict_receive_op.path_len, 2);
    assert_int_equal(operation.path_payment_strict_receive_op.path[0].type, asset2.type);
    assert_string_equal(operation.path_payment_strict_receive_op.path[0].alpha_num12.asset_code,
                        asset2.alpha_num12.asset_code);
    assert_memory_equal(operation.path_payment_strict_receive_op.path[1].alpha_num12.issuer,
                        asset3.alpha_num12.issuer,
                        sizeof(asset3.alpha_num12.issuer));
    assert_int_equal(operation.path_payment_strict_receive_op.path[1].type, asset3.type);
    assert_string_equal(operation.path_payment_strict_receive_op.path[1].alpha_num12.asset_code,
                        asset3.alpha_num12.asset_code);
    assert_memory_equal(operation.path_payment_strict_receive_op.path[1].alpha_num12.issuer,
                        asset3.alpha_num12.issuer,
                        sizeof(asset3.alpha_num12.issuer));
}

static void test_manage_sell_offer_op() {
    uint8_t data[] = {0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x62, 0x5f, 0x3d, 0x59, 0xc3,
                      0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda, 0x5e, 0x8,  0xc5, 0xd6, 0xe4, 0xbd, 0xf0,
                      0xd1, 0x50, 0x3a, 0xb9, 0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb, 0x9,  0x1e, 0x5d,
                      0xa1, 0x0,  0x0,  0x0,  0x3,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,
                      0x55, 0x53, 0x44, 0x0,  0x0,  0x0,  0x0,  0x0,  0x9b, 0x8e, 0xba, 0xf8, 0x96,
                      0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4, 0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87,
                      0xab, 0xe,  0x2d, 0xb3, 0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59,
                      0xd8, 0x0,  0x0,  0x0,  0x0,  0x5,  0xf5, 0xe1, 0x0,  0x0,  0x0,  0x0,  0x1,
                      0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0xe2, 0x40};

    buffer_t buffer = {.offset = 0, .size = sizeof(data), .ptr = data};
    operation_t operation;
    assert_true(read_operation(&buffer, &operation));
    assert_int_equal(buffer.offset, buffer.size);

    assert_true(operation.source_account_present);
    assert_int_equal(operation.source_account.type, KEY_TYPE_ED25519);
    assert_memory_equal(operation.source_account.ed25519, kp1_public, sizeof(kp1_public));

    assert_int_equal(operation.type, OPERATION_TYPE_MANAGE_SELL_OFFER);

    uint8_t issuer1[] = {0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4,
                         0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3,
                         0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8};
    asset_t asset1 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                      .alpha_num4 = {.asset_code = "USD", .issuer = issuer1}};

    assert_int_equal(operation.manage_sell_offer_op.selling.type, ASSET_TYPE_NATIVE);
    assert_int_equal(operation.manage_sell_offer_op.buying.type, asset1.type);
    assert_string_equal(operation.manage_sell_offer_op.buying.alpha_num4.asset_code,
                        asset1.alpha_num4.asset_code);
    assert_memory_equal(operation.manage_sell_offer_op.buying.alpha_num4.issuer,
                        asset1.alpha_num4.issuer,
                        sizeof(asset1.alpha_num4.issuer));
    assert_int_equal(operation.manage_sell_offer_op.amount, 100000000);
    assert_int_equal(operation.manage_sell_offer_op.price.n, 1);
    assert_int_equal(operation.manage_sell_offer_op.price.d, 1);
    assert_int_equal(operation.manage_sell_offer_op.offer_id, 123456);
}

static void test_create_passive_sell_offer_op() {
    uint8_t data[] = {0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x62, 0x5f, 0x3d, 0x59,
                      0xc3, 0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda, 0x5e, 0x8,  0xc5, 0xd6, 0xe4,
                      0xbd, 0xf0, 0xd1, 0x50, 0x3a, 0xb9, 0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb,
                      0x9,  0x1e, 0x5d, 0xa1, 0x0,  0x0,  0x0,  0x4,  0x0,  0x0,  0x0,  0x0,
                      0x0,  0x0,  0x0,  0x1,  0x55, 0x53, 0x44, 0x0,  0x0,  0x0,  0x0,  0x0,
                      0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4, 0xf7,
                      0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3, 0xd6, 0x9b,
                      0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8, 0x0,  0x0,  0x0,  0x0,
                      0x5,  0xf5, 0xe1, 0x0,  0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x1};

    buffer_t buffer = {.offset = 0, .size = sizeof(data), .ptr = data};
    operation_t operation;
    assert_true(read_operation(&buffer, &operation));
    assert_int_equal(buffer.offset, buffer.size);

    assert_true(operation.source_account_present);
    assert_int_equal(operation.source_account.type, KEY_TYPE_ED25519);
    assert_memory_equal(operation.source_account.ed25519, kp1_public, sizeof(kp1_public));

    assert_int_equal(operation.type, OPERATION_TYPE_CREATE_PASSIVE_SELL_OFFER);

    uint8_t issuer1[] = {0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4,
                         0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3,
                         0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8};
    asset_t asset1 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                      .alpha_num4 = {.asset_code = "USD", .issuer = issuer1}};

    assert_int_equal(operation.create_passive_sell_offer_op.selling.type, ASSET_TYPE_NATIVE);
    assert_int_equal(operation.create_passive_sell_offer_op.buying.type, asset1.type);
    assert_string_equal(operation.create_passive_sell_offer_op.buying.alpha_num4.asset_code,
                        asset1.alpha_num4.asset_code);
    assert_memory_equal(operation.create_passive_sell_offer_op.buying.alpha_num4.issuer,
                        asset1.alpha_num4.issuer,
                        sizeof(asset1.alpha_num4.issuer));
    assert_int_equal(operation.create_passive_sell_offer_op.amount, 100000000);
    assert_int_equal(operation.create_passive_sell_offer_op.price.n, 1);
    assert_int_equal(operation.create_passive_sell_offer_op.price.d, 1);
}

static void test_change_trust_op() {
    uint8_t data[] = {0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x62, 0x5f, 0x3d, 0x59,
                      0xc3, 0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda, 0x5e, 0x8,  0xc5, 0xd6, 0xe4,
                      0xbd, 0xf0, 0xd1, 0x50, 0x3a, 0xb9, 0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb,
                      0x9,  0x1e, 0x5d, 0xa1, 0x0,  0x0,  0x0,  0x6,  0x0,  0x0,  0x0,  0x1,
                      0x55, 0x53, 0x44, 0x0,  0x0,  0x0,  0x0,  0x0,  0x9b, 0x8e, 0xba, 0xf8,
                      0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4, 0xf7, 0x43, 0x20, 0x71, 0x10,
                      0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3, 0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22,
                      0x72, 0xf7, 0x59, 0xd8, 0x0,  0x0,  0x0,  0x0,  0x5,  0xf5, 0xe1, 0x0};

    buffer_t buffer = {.offset = 0, .size = sizeof(data), .ptr = data};
    operation_t operation;
    assert_true(read_operation(&buffer, &operation));
    assert_int_equal(buffer.offset, buffer.size);

    assert_true(operation.source_account_present);
    assert_int_equal(operation.source_account.type, KEY_TYPE_ED25519);
    assert_memory_equal(operation.source_account.ed25519, kp1_public, sizeof(kp1_public));

    assert_int_equal(operation.type, OPERATION_TYPE_CHANGE_TRUST);

    uint8_t issuer1[] = {0x9b, 0x8e, 0xba, 0xf8, 0x96, 0x38, 0x55, 0x1d, 0xcf, 0x9e, 0xa4,
                         0xf7, 0x43, 0x20, 0x71, 0x10, 0x6b, 0x87, 0xab, 0xe,  0x2d, 0xb3,
                         0xd6, 0x9b, 0x75, 0xa5, 0x38, 0x22, 0x72, 0xf7, 0x59, 0xd8};
    asset_t asset1 = {.type = ASSET_TYPE_CREDIT_ALPHANUM4,
                      .alpha_num4 = {.asset_code = "USD", .issuer = issuer1}};

    assert_int_equal(operation.change_trust_op.line.type, asset1.type);
    assert_string_equal(operation.change_trust_op.line.alpha_num4.asset_code,
                        asset1.alpha_num4.asset_code);
    assert_memory_equal(operation.change_trust_op.line.alpha_num4.issuer,
                        asset1.alpha_num4.issuer,
                        sizeof(asset1.alpha_num4.issuer));
    assert_int_equal(operation.change_trust_op.limit, 100000000);
}

static void test_allow_trust_op() {
    uint8_t data[] = {0x0,  0x0,  0x0,  0x1,  0x0,  0x0,  0x0,  0x0,  0x62, 0x5f, 0x3d, 0x59,
                      0xc3, 0xf8, 0x9e, 0x59, 0x1a, 0x6,  0xda, 0x5e, 0x8,  0xc5, 0xd6, 0xe4,
                      0xbd, 0xf0, 0xd1, 0x50, 0x3a, 0xb9, 0xc3, 0x22, 0x81, 0x49, 0x49, 0xeb,
                      0x9,  0x1e, 0x5d, 0xa1, 0x0,  0x0,  0x0,  0x7,  0x0,  0x0,  0x0,  0x0,
                      0xb4, 0x69, 0xf8, 0x27, 0xc2, 0x68, 0xa1, 0xfe, 0x55, 0x2,  0xaf, 0x55,
                      0x87, 0x1,  0x11, 0x16, 0x23, 0xe3, 0xbf, 0xf8, 0x81, 0x74, 0xb3, 0xb0,
                      0x6d, 0x56, 0x48, 0x8c, 0xc5, 0x2e, 0xfe, 0xb8, 0x0,  0x0,  0x0,  0x1,
                      0x55, 0x53, 0x44, 0x0,  0x0,  0x0,  0x0,  0x1};

    buffer_t buffer = {.offset = 0, .size = sizeof(data), .ptr = data};
    operation_t operation;
    assert_true(read_operation(&buffer, &operation));
    assert_int_equal(buffer.offset, buffer.size);

    assert_true(operation.source_account_present);
    assert_int_equal(operation.source_account.type, KEY_TYPE_ED25519);
    assert_memory_equal(operation.source_account.ed25519, kp1_public, sizeof(kp1_public));

    assert_int_equal(operation.type, OPERATION_TYPE_ALLOW_TRUST);
    assert_memory_equal(operation.allow_trust_op.trustor, kp2_public, sizeof(kp2_public));
    assert_string_equal(operation.allow_trust_op.asset_code, "USD");
    assert_int_equal(operation.allow_trust_op.authorize, AUTHORIZED_FLAG);
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
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}