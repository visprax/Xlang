#ifndef XLANG_LOGGER_H
#define XLANG_LOGGER_H

#include "common.h"

// maximum datetime buffer length
#define MAX_DT_BUF_LEN 64

typedef struct
{
    char* red;
    char* green;
    char* yellow;
    char* blue;
    char* magenta;
    char* cyan;
    char* reset;
} Colors;

typedef enum
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
} LogLevel;

void logger(const char* name, const uint8_t level, const char* message, ...);

#endif // XLANG_LOGGER_H
