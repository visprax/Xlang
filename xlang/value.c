#include <stdio.h>

#include "logger.h"
#include "memory.h"
#include "value.h"

void init_valuearray(ValueArray* array)
{
    logger("INFO", "initializing ValueArray");
    array->size = 0;
    array->capacity = 0;
    array->values = NULL;
}

void write_valuearray(ValueArray* array, Value value)
{
    logger("INFO", "writing to ValueArray, Value: %lf", value);
    if (array->capacity < array->size+1)
    {
        logger("DEBUG", "increasing ValueArray capacity");
        int old_capacity = array->capacity;
        array->capacity = GROW_CAPACITY(old_capacity);
        array->values = GROW_ARRAY(Value, array->values, old_capacity, array->capacity);
    }

    array->values[array->size] = value;
    array->size++;
}

void free_valuearray(ValueArray* array)
{
    logger("INFO", "freeing ValueArray");
    FREE_ARRAY(Value, array->values, array->capacity);
    init_valuearray(array);
}
