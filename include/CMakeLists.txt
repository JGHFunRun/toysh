target_include_directories(toysh PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(cmakedefs.h.in cmakedefs.h)
target_include_directories(toysh PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
