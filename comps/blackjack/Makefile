CC = gcc
CFLAGS = -Wall -Wextra -ggdb --std=c99

blackjack: blackjack.o
	$(CC) $(CFLAGS) -o $@ $?

#compile
blackjack.o: blackjack.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf *.o blackjack