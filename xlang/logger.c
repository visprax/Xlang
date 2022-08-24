#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#include "logger.h"

void logger(const char* level, const char* message, ...)
{
    time_t now = time(NULL);
    struct tm* datetime = localtime(&now);
    
    char datetime_buff[64];
    strftime(datetime_buff, sizeof datetime_buff, "%d-%b-%Y %X", datetime);
    // variadic arguments
    va_list args;
    va_start(args, message);
    fprintf(stderr, "[%s] %8s: ", datetime_buff, level);
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n")
    va_end(args);
}
