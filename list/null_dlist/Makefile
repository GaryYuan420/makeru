CC = gcc
CFLAGS =  -g -Wall

test:test.o dlist.o
	$(CC) $(CFLAGS) -o $@ $^
.PHONY:clean
clean:
	rm  test *.o
