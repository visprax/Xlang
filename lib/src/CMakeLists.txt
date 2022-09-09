add_library(logger SHARED logger.c)
target_include_directories(logger PUBLIC ${PROJECT_SOURCE_DIR}/lib/inc)
