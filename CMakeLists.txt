cmake_minimum_required(VERSION 3.22)
project(stellar C)

set(CMAKE_C_STANDARD 99)

add_library(stellar src/reader.c src/writer.c src/utils.c)
