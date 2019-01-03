#include <stdio.h>
#include <stdlib.h>
#include "seqlist.h"
int main(int argc, const char *argv[])
{
	int i=0;
	seqlist_t *L=NULL;
	int num[] = {1,2,3,3,3,6,7,8,9};
	L=create_seqlsit();
	fill_seqlist(L,num,sizeof(num)/sizeof(int));//调用数据填充函数
	derep_seqlist(L);//调用去重函数
	show_seqlist(L);
	clear_seqlsit(L);

	return 0;
}

