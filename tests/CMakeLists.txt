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

file(GLOB sha256_src
        "../src/vendor/sha256/*.h"
        "../src/vendor/sha256/*.c"
        )

add_library(
        stellar_base
        ${ed25519_src}
        ${crc16_src}
        ${base32_src}
        ${base58_src}
        ${base64_src}
        ${sha256_src}
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

add_executable(test_decorated_signature src/test_decorated_signature.c)
target_link_libraries(test_decorated_signature PRIVATE cmocka stellar_base)
add_test(test_decorated_signature test_decorated_signature)

add_executable(test_network src/test_network.c)
target_link_libraries(test_network PRIVATE cmocka stellar_base)
add_test(test_network test_network)

add_executable(test_transaction_envelope src/test_transaction_envelope.c)
target_link_libraries(test_transaction_envelope PRIVATE cmocka stellar_base)
add_test(test_transaction_envelope test_transaction_envelope)

add_executable(test_asset src/test_asset.c)
target_link_libraries(test_asset PRIVATE cmocka stellar_base)
add_test(test_asset test_asset)

add_executable(test_liquidity_pool_asset src/test_liquidity_pool_asset.c)
target_link_libraries(test_liquidity_pool_asset PRIVATE cmocka stellar_base)
add_test(test_liquidity_pool_asset test_liquidity_pool_asset)

add_executable(test_fee_bump_transaction src/test_fee_bump_transaction.c)
target_link_libraries(test_fee_bump_transaction PRIVATE cmocka stellar_base)
add_test(test_fee_bump_transaction test_fee_bump_transaction)