CC=gcc
CFlAGS=-Wall -Wextra -ggdb 
DEPS = randomizer.h

%o.: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFlAGS)

randomizer: randomizer.o
	$(CC) -o randomizer randomizer.o