cmake_minimum_required(VERSION 3.22)
project(test_libstellar C)

# guard against bad build-type strings
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

include(CTest)
ENABLE_TESTING()

# specify C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -pedantic -g -O0 --coverage")

if (UNIX AND NOT APPLE)
    set(GCC_COVERAGE_LINK_FLAGS "--coverage -lgcov")
endif ()
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

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

file(GLOB libstellar_test_include_src
        "include/*.h"
        "include/*.c"
        )

add_library(
        libstellar_test
        ${libstellar_test_include_src}
)

add_executable(test_utils test_utils.c)
if (UNIX AND NOT APPLE)
    target_link_libraries(test_utils PRIVATE cmocka libstellar bsd)
else ()
    target_link_libraries(test_utils PRIVATE cmocka libstellar)
endif ()
add_test(test_utils test_utils)

add_executable(test_reader test_reader.c)
if (UNIX AND NOT APPLE)
    target_link_libraries(test_reader PRIVATE cmocka libstellar bsd)
else ()
    target_link_libraries(test_reader PRIVATE cmocka libstellar)
endif ()
add_test(test_reader test_reader)

add_executable(test_writer test_writer.c)
if (UNIX AND NOT APPLE)
    target_link_libraries(test_writer PRIVATE cmocka libstellar libstellar_test bsd)
else ()
    target_link_libraries(test_writer PRIVATE cmocka libstellar libstellar_test)
endif ()
add_test(test_writer test_writer)
