#include "net.h"

int main()
{
	int fd = -1;
	struct sockaddr_in sin;
	if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
			perror("socket");
			exit(1);
	}
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(SERV_PORT);
	if(inet_pton(AF_INET, SERV_IP_ADDR, (void *)&sin.sin_addr) != 1){
			perror("inet_pton");
			exit(1);
	}
	if(connect(fd,(struct sockaddr *)&sin, sizeof(sin)) < 0){
			perror("socket");
			exit(1);
	}
	printf("client starting....\n");
	char buf[BUFSIZ];
	int ret = -1;
	while(1){
		bzero(buf, BUFSIZ);
		if(fgets(buf, BUFSIZ -1, stdin) == NULL){
			continue;
		}
		do{
			ret = send(fd, buf, strlen(buf), 0);
		}while(ret < 0 && EINTR == errno);
		if(!strncasecmp(buf, QUIT_STR, strlen(QUIT_STR))){
			printf("client is exiting!\n");
			break;
		}
	}
	close(fd);
	return 0;

}
