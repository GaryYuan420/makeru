CC = gcc
CFLAGS = -o0 -g -Wall

test:test.o linklist.o
	$(CC) $(CFLAGS) -o $@ $^
.PHONY:clean
clean:
	rm  test *.o
