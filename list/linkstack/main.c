#include"linkstack.h"


int main(){
	listlink H;
	H = listcreat();
	
	listpush(H, 10);
	listpush(H, 20);
	listpush(H, 30);
	listpush(H, 40);
	listpush(H, 50);

	while(is_emptylist(H) == 0){
		printf("%d\t",listpop(H));	
	}
	printf("\n");
	dellist(H);
	return 0;
	
}
