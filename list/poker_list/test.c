#include "linklist.h"
#define cardnum  13
int main(int argc, const char *argv[])
{
	linklist H, p;
	int i, count_num;

	H=list_create();//创建循环链表头
	for(i=0;i<cardnum-1;i++){
		list_head_insert(H,0);//创建还有13个节点的空列表，表示13张牌
	}
	list_show(H);
	p = H;
	for(count_num=1;count_num<cardnum + 1;count_num++){
		for(i=0;i<2;i++){//每次拿两张牌
			p = p->next;
			while(p->data != 0)
				p = p->next;		
		}
		p->data = count_num;

	}

	list_show(H);

	return 0;
}
