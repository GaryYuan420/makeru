#ifndef __DLIST_H__
#define __DLIST_H__

#include <stdio.h>
#include <stdlib.h>

typedef int data_t;

typedef struct node{
	data_t data;
	struct node *prior;
	struct node *next;
}dlistnode;

extern dlistnode* dlist_create();
extern void dlist_show(dlistnode* H);

#endif
