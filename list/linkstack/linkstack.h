#ifndef linkstack_H
#define linkstack_H

#include<stdio.h>
#include<stdlib.h>

typedef int data_t;
typedef struct node{
	data_t data;
	struct node *next;
}listnode, *listlink;

extern listlink listcreat();
extern int listpush(listlink H, int val);
extern int listpop(listlink H);
extern int is_emptylist(listlink H);
extern void dellist(listlink H);

#endif
