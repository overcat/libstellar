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

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_account_op),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}