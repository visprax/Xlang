#ifndef XLANG_VALUE_H
#define XLANG_VALUE_H

#include "common.h"

typedef double Value;

/*
 * For small fix-sized values like integers, many instruction sets 
 * store the value directly at the code stream right after the opcode, 
 * these are called immediate instructions, because the bits for the 
 * value are immediately after the opcode. For large or variable-sized 
 * constants like strings, this doesn't work. In a native compiler to 
 * machine code, those bigger constants get stored in a separate 
 * "constant data" region in the binary executable, then the instruction 
 * to load a constant has an address or offset pointing to where the value 
 * is stored in that section. Most virtual machines will do something similar, 
 * e.g. constant pool in JVM. Here each bytecode stream will carry with it 
 * a list of the values that appear as literals in the program.
 */
typedef struct 
{
    Value* values;
    int capacity;
    int size;
} ValueArray;

void init_valuearray(ValueArray* array);
void write_valuearray(ValueArray* array, Value value);
void free_valuearray(ValueArray* array);
void print_value(Value value);

#endif // XLANG_VALUE_H
