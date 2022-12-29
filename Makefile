CC=gcc
CFLAGS=-Ofast

row-counter: main.c
	$(CC) $(CFLAGS) main.c -o row-counter

install: row-counter
	cp row-counter /bin/
