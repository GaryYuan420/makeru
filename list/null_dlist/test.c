#include "dlist.h"

int main(int argc, const char *argv[])
{
	dlistnode *H;
	if((H=(dlistnode *)malloc(sizeof(dlistnode)))==NULL)
	{
		puts("malloc failed");
		return -1;
	}

	H->prior = H;
	H->next = H;

	return 0;
}

