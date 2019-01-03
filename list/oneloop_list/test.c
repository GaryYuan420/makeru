#include "linklist.h"

int main(int argc, const char *argv[])
{
	linklist H;
#if 0
	H=list_create();
	list_head_insert(H,10);
	list_head_insert(H,20);
	list_head_insert(H,30);
#endif
	H=list_create2();

	list_show(H);
	return 0;
}
