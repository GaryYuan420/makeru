CC = gcc
CFLAGS =-O0 -g -Wall

test:property.c ReadDir.c
	$(CC) $(CFLAGS) -o $@ $^
.PHONY:clean
clean:
	rm -rf test
