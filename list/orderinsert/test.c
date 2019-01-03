#include "linklist.h"

int main(int argc, const char *argv[])
{
//	linklist p;
	linklist H;
	int inval;
	printf("BIG2SMALL order\n");
	H=list_create();
	list_head_insert(H,10);
	list_head_insert(H,20);
	list_head_insert(H,30);
	list_show(H);
	printf("please input value:");
	scanf("%d",&inval);
	if((list_order_insert(H,inval,BIG2SMALL))==-1){
		printf("insert failed\n");
	}
	list_show(H);
	return 0;
}
