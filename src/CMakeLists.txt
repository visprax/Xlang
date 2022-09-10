add_executable(xlang main.c)
target_sources(xlang PRIVATE bcstream.c debugger.c memory.c value.c vm.c) 

# TODO: use presets of cmake for maintaining flags
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_options(xlang PRIVATE /W4)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(xlang PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_options(xlang PRIVATE -Weverything)
endif()

target_include_directories(xlang PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_include_directories(xlang PUBLIC ${PROJECT_SOURCE_DIR}/lib/inc)

target_link_libraries(xlang LINK_PUBLIC logger)
