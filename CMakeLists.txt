cmake_minimum_required(VERSION 3.1...3.24)

project(XLANG VERSION 0.1 LANGUAGES C)

add_subdirectory(src)
add_subdirectory(lib)

if(testing_enabled)
    add_subdirectory(tests)
endif()

macro(MACRO_ENSURE_OUT_OF_SOURCE_BUILD MSG)
    string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" insource)
    get_filename_component(PARENTDIR ${CMAKE_SOURCE_DIR} PATH)
    string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${PARENTDIR}" insourcesubdir)
    if(insource OR insourcesubdir)
        message(FATAL_ERROR "${MSG}")
    endif(insource OR insourcesubdir)
endmacro(MACRO_ENSURE_OUT_OF_SOURCE_BUILD)
MACRO_ENSURE_OUT_OF_SOURCE_BUILD("${CMAKE_PROJECT_NAME} requires an out of source build.")
