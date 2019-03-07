CC=gcc
CFLAGS = -I -Wextra
DEPS = echoserver.h
OBJ = echoserver.o socketutils.o echoclient.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

echoserver: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
