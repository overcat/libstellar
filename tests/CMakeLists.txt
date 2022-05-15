cmake_minimum_required(VERSION 3.22)
project(test_libstellar C)

set(CMAKE_C_STANDARD 99)

enable_testing()

add_compile_options(-g -ggdb2)

file(GLOB libstellar_include_src
        "../src/include/*.h"
        "../src/include/*.c"
        )

file(GLOB libstellar_src
        "../src/*.h"
        "../src/*.c"
        )

add_library(
        libstellar
        ${libstellar_include_src}
        ${libstellar_src}
)

add_executable(test_utils test_utils.c)
if (UNIX AND NOT APPLE)
    target_link_libraries(test_utils PRIVATE cmocka libstellar bsd)
else ()
    target_link_libraries(test_utils PRIVATE cmocka libstellar)
endif ()
add_test(test_utils test_utils)
