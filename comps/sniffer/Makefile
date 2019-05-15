CC = gcc
CFLAGS = -Wall -Wextra -ggdb --std=c99

sniffer: sniffer.o
	$(CC) $(CFLAGS) -o $@ $?

#compile
sniffer.o: sniffer.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf *.o sniffer