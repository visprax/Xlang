#include <stdio.h>

#include "logger.h"
#include "memory.h"
#include "value.h"

static char* LOGNAME = "value";

void init_valuearray(ValueArray* array)
{
    logger(LOGNAME, INFO, "initializing ValueArray");
    array->size = 0;
    array->capacity = 0;
    array->values = NULL;
}

void write_valuearray(ValueArray* array, Value value)
{
    logger(LOGNAME, INFO, "writing to ValueArray, Value: %lf", value);
    if (array->capacity < array->size+1)
    {
        logger(LOGNAME, DEBUG, "increasing ValueArray capacity");
        int old_capacity = array->capacity;
        array->capacity = GROW_CAPACITY(old_capacity);
        array->values = GROW_ARRAY(Value, array->values, old_capacity, array->capacity);
    }

    array->values[array->size] = value;
    array->size++;
}

void free_valuearray(ValueArray* array)
{
    logger(LOGNAME, INFO, "freeing ValueArray");
    FREE_ARRAY(Value, array->values, array->capacity);
    init_valuearray(array);
}