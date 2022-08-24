CC := gcc -g -Wall

all: xlang.x

xlang.x: main.o logger.o memory.o bytecode.o
	$(CC) main.o logger.o memory.o bytecode.o -o xlang.x

main.o: main.c
	$(CC) -c main.c

logger.o: logger.c
	$(CC) -c logger.c

memory.o: memory.c
	$(CC) -c memory.c

bytecode.o: bytecode.c
	$(CC) -c bytecode.c

.PHONY: clean run

clean:
	rm xlang.x *.o

run:
	./xlang.x

