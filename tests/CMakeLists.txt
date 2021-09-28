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
