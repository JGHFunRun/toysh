cmake_minimum_required(VERSION 3.12...3.28)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED On)

project(toysh
	VERSION 0.0.0
	HOMEPAGE_URL https://jghfunrun.github.io/ToySH
	LANGUAGES C)

add_executable(toysh src/main.c src/args.c
	src/shell.c src/lexer.c
	src/filemgmt.c src/charsets.c src/alloc.c src/errors.c src/sstring.c)

add_subdirectory(include/)

add_subdirectory(doc/)
add_subdirectory(man/)
