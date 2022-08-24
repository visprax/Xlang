#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "logger.h"

void logger(const char* level, const char* message)
{
    time_t now;
    time(&now);
    fprintf(stderr, "[%s] %8s: %s\n", ctime(&now), level, message);
}
