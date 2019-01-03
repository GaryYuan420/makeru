#include"linkstack.h"

listlink listcreat(){
	listlink p;
	if((p = (listlink)malloc(sizeof(listnode))) == NULL){
		printf("malloc error\n");
		return NULL;
	}
	p->next = NULL;
	return p;
}

int listpush(listlink H, int val){
	listlink p;
	if((p = (listlink)malloc(sizeof(listnode))) == NULL){
		printf("malloc error\n");
		return -1;
	}
	p->data = val;
	p->next = H->next;
	H->next = p;
	return 0;
}

int listpop(listlink H){
	listlink p;
	int ret;
	if((p = (listlink)malloc(sizeof(listnode))) == NULL){
		printf("malloc error\n");
		return -1;
	}
	if((p = H->next) == NULL){
		printf("list is NULL\n");
		return -1;
	}
	
	ret = p->data;
	H->next = p->next;
	free(p);
	return ret;	
}

int is_emptylist(listlink H){
	return(H->next == NULL? 1:0);
}

void dellist(listlink H){
	listlink p, q;
	if((p = (listlink)malloc(sizeof(listnode))) == NULL){
		printf("malloc error\n");
	}
	p = H->next;
	while(p){
		q = p;
		p = p->next;
		free(q);
	}
	free(H);
}





