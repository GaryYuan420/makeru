#include <stdio.h>
#include <stdlib.h>
#include "seqlist.h"
int main(int argc, const char *argv[])
{
	int i=0;
	seqlist_t *L1=NULL;
	seqlist_t *L2=NULL;
	int num1[] = {1,2,3,4,5,6};
	int num2[] = {5,6,7,8,9,10};
	L1=create_seqlsit();
	L2=create_seqlsit();
	fill_seqlist(L1,num1,sizeof(num1)/sizeof(int));//调用填充函数
	fill_seqlist(L2,num2,sizeof(num2)/sizeof(int));
	merge_seqlist(L1,L2);//调用合并函数
	show_seqlist(L1);
	//show_seqlist(L2);
	
	clear_seqlsit(L1);
	clear_seqlsit(L2);

	return 0;
}

