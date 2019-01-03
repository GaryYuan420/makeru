#include "net.h"
int main(int argc,char* argv[])
{
	struct hostent* h;
	if(argc != 2){
		printf("USAGE: %s <hostname>",argv[0]);
		exit(1);
	}
	if( (h = gethostbyname(argv[1])) ==NULL){
		herror("gethostbyname");
		exit(1);
	}
	struct in_addr addr;
	addr.s_addr = *(u_long*)(h->h_addr_list[0]);
	printf("hostname: %s\n", h->h_name);
	printf("IPAddress: %s\n",inet_ntoa(addr));
	return 0;
}

