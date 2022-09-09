#ifndef XLANG_VALUE_H
#define XLANG_VALUE_H

#include "common.h"

typedef double Value;

typedef struct 
{
    int size;
    int capacity;
    Value* values;
} ValueArray;

void init_valuearray(ValueArray* array);
void write_valuearray(ValueArray* array, Value value);
void free_valuearray(ValueArray* array);
void print_value(Value value);

#endif // XLANG_VALUE_H
