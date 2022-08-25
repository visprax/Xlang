CC := gcc -g -Wall

all: xlang.x

xlang.x: main.o logger.o memory.o bytecode.o debugger.o value.o
	$(CC) main.o logger.o memory.o bytecode.o debugger.o value.o -o xlang.x

main.o: main.c
	$(CC) -c main.c

logger.o: logger.c
	$(CC) -c logger.c

memory.o: memory.c
	$(CC) -c memory.c

bytecode.o: bytecode.c
	$(CC) -c bytecode.c

debugger.o: debugger.c
	$(CC) -c debugger.c

value.o: value.c
	$(CC) -c value.c

.PHONY: clean run

clean:
	rm -rf xlang.x *.o

run: xlang.x
	./xlang.x

