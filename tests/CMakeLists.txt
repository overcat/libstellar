cmake_minimum_required(VERSION 3.10)
project(test_stellar_base C)

set(CMAKE_C_STANDARD 99)

enable_testing()

add_compile_options(-g -ggdb2)

file(GLOB ed25519_src
        "../src/vendor/ed25519/*.h"
        "../src/vendor/ed25519/*.c"
        )

file(GLOB stellar_base_src
        "../src/*.h"
        "../src/*.c"
        )

file(GLOB crc16_src
        "../src/vendor/crc16/*.h"
        "../src/vendor/crc16/*.c"
        )

file(GLOB base32_src
        "../src/vendor/base32/*.h"
        "../src/vendor/base32/*.c"
        )

file(GLOB base58_src
        "../src/vendor/base58/*.h"
        "../src/vendor/base58/*.c"
        )

file(GLOB base64_src
        "../src/vendor/base64/*.h"
        "../src/vendor/base64/*.c"
        )

add_library(
        stellar_base
        ${ed25519_src}
        ${crc16_src}
        ${base32_src}
        ${base58_src}
        ${base64_src}
        ${stellar_base_src}
)

add_executable(test_strkey src/test_strkey.c)
target_link_libraries(test_strkey PRIVATE cmocka stellar_base)
add_test(test_strkey test_strkey)

add_executable(test_keypair src/test_keypair.c)
target_link_libraries(test_keypair PRIVATE cmocka stellar_base)
add_test(test_keypair test_keypair)

add_executable(test_memo src/test_memo.c)
target_link_libraries(test_memo PRIVATE cmocka stellar_base)
add_test(test_memo test_memo)

add_executable(test_muxed_account src/test_muxed_account.c)
target_link_libraries(test_muxed_account PRIVATE cmocka stellar_base)
add_test(test_muxed_account test_muxed_account)

add_executable(test_operation src/test_operation.c)
target_link_libraries(test_operation PRIVATE cmocka stellar_base)
add_test(test_operation test_operation)

add_executable(test_transaction src/test_transaction.c)
target_link_libraries(test_transaction PRIVATE cmocka stellar_base)
add_test(test_transaction test_transaction)

add_executable(test_time_bounds src/test_time_bounds.c)
target_link_libraries(test_time_bounds PRIVATE cmocka stellar_base)
add_test(test_time_bounds test_time_bounds)


add_executable(test_price src/test_price.c)
target_link_libraries(test_price PRIVATE cmocka stellar_base)
add_test(test_price test_price)