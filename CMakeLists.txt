cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 23)

project(toysh
        VERSION 0.0.0
        LANGUAGES C)

add_executable(toysh src/main.c src/args.c
	src/shell.c src/lexer.c
	src/filemgmt.c src/charsets.c src/alloc.c)

target_include_directories(toysh PRIVATE include/)

add_subdirectory(doc/)
