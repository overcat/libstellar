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

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_account_op),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}