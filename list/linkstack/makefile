pushstack:main.o linkstack.o
	cc main.o linkstack.o -o pushstack
main.o:main.c
	cc -c main.c 
linkstack.o:linkstack.c
	cc -c linkstack.c 
clean:
	rm *.o pushstack
	
