#include "linklist.h"
linklist list_create()
{
	linklist H;
	if((H=(linklist)malloc(sizeof(listnode)))==NULL)
	{
		printf("malloc failed!\n");
		return H;
	}
	H->data = 0;
	H->next = NULL;

	return H;
}

linklist list_create2()
{
	linklist H,r,p;
	char value;
	if((H=(linklist)malloc(sizeof(listnode)))==NULL)
	{
		printf("malloc failed!\n");
		return H;
	}
	H->data = 0;
	H->next = NULL;
	r=H;

	while(1)
	{
		printf("input a number(# exit):");
		scanf("%c",&value);
		getchar();
		if(value == '#')
			break;
		if((p=(linklist)malloc(sizeof(listnode)))==NULL)
		{
			printf("malloc failed\n");
			return H;
		}
		p->data = value;
		p->next = NULL;
		r->next = p;
		r=p;
	}
	return H;
}
int list_head_insert(linklist H,datatype value)
{
	linklist p;

	if((p=(linklist)malloc(sizeof(listnode)))==NULL)
	{
		printf("malloc failed\n");
		return -1;
	}
	p->data = value;
	p->next = H->next;
	H->next = p;

	return 0;
}
void list_show(linklist H)
{
	while(H->next)
	{
		printf("%c ",H->next->data);
		H = H->next;
	}
	printf("\n");
}
