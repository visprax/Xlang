#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "bcstream.h"
#include "debugger.h"
#include "logger.h"
#include "vm.h"

static char* LOGNAME = "main";

static void repl()
{
    logger(LOGNAME, INFO, "dropping to REPL");

    char line[1024];
    for(;;)
    {
        printf("> ");

        if(!fgets(line, sizeof(line), stdin))
        {
            printf("\n");
            break;
        }

        interpret(line);
    }
}

static void run_file(const char* path)
{
    logger(LOGNAME, DEBUG, "running file: %s", path);

    char* source = read_file(path);
    InterpretResult result = interpret(source);
    free(source);

    if(result == INTERPRET_COMPILE_ERROR) exit(70);
    if(result == INTERPRET_RUNTIME_ERROR) exit(75);
}

static char* read_file(const char* path)
{
    logger(LOGNAME, INFO, "opening file: %s", path);

    FILE* file = fopen(path, "rb");
    if(file == NULL)
    {
        fprintf(stderr, "Could not open file: %s\n", path);
        exit(74);
    }
    
    // figure out the bytesize of the file
    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    // allocate one extra byte for the null byte at the end
    char* buffer = (char*)malloc(file_size + 1);
    if(buffer == NULL)
    {
        fprintf(stderr, "Not enough memory to read file: %s", path);
        exit(74);
    }
    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if(bytes_read < file_size)
    {
        fprintf(stderr, "Could not read file: %s", path);
        exit(74);
    }
    buffer[bytes_read] = "\0";

    fclose(file);
    return buffer;
}

// TODO: move hand compilation example to tests directory
int main(int argc, const char** argv)
{
    logger(LOGNAME, INFO, "hand compiling an example AST to bytecode");

    init_vm();
    /*BCStream bcstream;*/
    /*init_bcstream(&bcstream);*/
    
    /*
     * Here we add a constant to the bytecode stream constant pool,
     * this returns the index of the constant in the array, then we
     * write the constant instruction starting with its opcode,
     * after that we write the one-byte constant index operand.
     */
    /*int constant = add_constant(&bcstream, 1.0);*/
    /*write_bcstream(&bcstream, OP_CONSTANT, 100); // the line numbers are arbitrary*/
    /*write_bcstream(&bcstream, constant, 100);*/

    /*constant = add_constant(&bcstream, 1.5);*/
    /*write_bcstream(&bcstream, OP_CONSTANT, 100);*/
    /*write_bcstream(&bcstream, constant, 100);*/

    /*write_bcstream(&bcstream, OP_ADD, 100);*/

    /*constant = add_constant(&bcstream, 2.0);*/
    /*write_bcstream(&bcstream, OP_CONSTANT, 100);*/
    /*write_bcstream(&bcstream, constant, 100);*/

    /*write_bcstream(&bcstream, OP_DIVIDE, 100);*/
    /*write_bcstream(&bcstream, OP_NEGATE, 100);*/

    /*write_bcstream(&bcstream, OP_RETURN, 100);*/
    
    /*disassemble_bcstream(&bcstream, "Test Bytecode Stream");*/
    /*interpret(&bcstream);*/

    if(argc == 1)
    {
        repl();
    }
    else if(argc == 2)
    {
        run_file(argv[1]);
    }
    else
    {
        fprintf(stderr, "Usage: xlang <path>\n");
        exit(60);
    }

    free_vm();
    /*free_bcstream(&bcstream);*/
    return 0;
}
