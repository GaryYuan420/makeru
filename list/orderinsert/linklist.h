#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdio.h>
#include <stdlib.h>

#define BIG2SMALL 1
#define SMALL2BIG 0
typedef int datatype;

typedef struct node{
	datatype data;
	struct node *next;
}listnode,*linklist;

extern linklist list_create();
extern linklist list_create2();
extern int list_head_insert(linklist H,datatype value);
extern int list_insert(linklist H,int pos,datatype value);
extern int list_order_insert(linklist H,datatype value,int order);
extern linklist list_get(linklist H,int pos);
extern linklist list_locate(linklist H,datatype value);
extern void list_show(linklist H);

#endif
