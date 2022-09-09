cmake_minimum_required(VERSION 3.1...3.24)

project(XLANG VERSION 0.1 LANGUAGES C)

add_subdirectory(src)
add_subdirectory(lib)

if(testing_enabled)
    add_subdirectory(tests)
endif()
