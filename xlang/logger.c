#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "logger.h"

// TODO: make log levels an enum
// TODO: set a name for the logger (e.g. main, memory, ...)
// TODO: a way to enable or disable logging or setting log level

static char* LOGNAME = "logger";

void logger(const char* name, const uint8_t level, const char* message, ...)
{
    Colors colors = {
        "\x1b[31m",
        "\x1b[32m",
        "\x1b[33m",
        "\x1b[34m",
        "\x1b[35m",
        "\x1b[36m",
        "\x1b[0m"
    };

    const char* level_color;
    const char* level_name;
    switch (level)
    {
        case DEBUG:
            level_color = colors.green;
            level_name = "DEBUG";
            break;
        case INFO:
            level_color = colors.yellow;
            level_name = "INFO";
            break;
        case WARNING:
            level_color = colors.blue;
            level_name = "WARNING";
            break;
        case ERROR:
            level_color = colors.red;
            level_name = "ERROR";
            break;
        case CRITICAL:
            level_color = colors.red;
            level_name = "CRITICAL";
            break;
        default:
            logger(LOGNAME, ERROR, "no support for logging level: %s", level);
            exit(EXIT_FAILURE);
    }

    time_t now = time(NULL);
    struct tm* datetime = localtime(&now);
    char datetime_buff[MAX_DT_BUF_LEN];
    strftime(datetime_buff, sizeof(datetime_buff), "%d-%b-%Y %X", datetime);

    // variadic arguments
    va_list args;
    va_start(args, message);
    fprintf(stderr, "%s[%s]%s %8s %s%5s%s: ", colors.cyan, datetime_buff, 
            colors.reset, name, level_color, level_name, colors.reset);
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
    va_end(args);
}
