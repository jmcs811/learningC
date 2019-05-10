CC = gcc
DEPS = echoserver.h
CFLAGS = -Wall -Wextra -ggdb --std=c99
OBJ = echoserver.o socketutils.o
ALL = echoserver echoclient
 
all: $(ALL)

#compile
echoserver: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

echoclient: echoclient.o socketutils.o
	$(CC) -o $@ $^ $(CFLAGS)

#link
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

echoserver: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o echoserver echoclient
