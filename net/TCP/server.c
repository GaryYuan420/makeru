#include"net.h"

int main(int argc, char* argv[])
{
	int fd = -1;
	struct sockaddr_in sin;
	if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket:");
		exit(1);	
	}
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(SERV_PORT);
	printf("server ip is %s, PORT is %d\n",SERV_IP_ADDR,SERV_PORT);
	if(inet_pton(AF_INET, SERV_IP_ADDR,(void *)&sin.sin_addr) != 1){
		perror("inet_pton");
		exit(1);	
	}
	if(bind(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0){
		perror("bind");
		exit(1);		
	}
	if(listen(fd, BACKLOG) < 0){
		perror("listen");
		exit(1);
	}
	printf("server starting.....OK!\n");
	int con_fd = -1;
	struct sockaddr_in cin;
	socklen_t addrlen = sizeof(cin);
	if((con_fd = accept(fd, (struct sockaddr *)&cin, &addrlen)) < 0){
		perror("accept");
		exit(1);	
	}
	printf("accept!\n");
	char client_addr[16];
	if(!inet_ntop(AF_INET, (void *)&cin.sin_addr, client_addr, sizeof(client_addr)) < 0){
		perror("inet_pton");
		exit(1);	
	}
	printf("client is %s:%d\n",client_addr,ntohs(cin.sin_port));
	int ret = -1;
	char buf[BUFSIZ];
	while(1){
		bzero(buf,BUFSIZ);
		do{
			ret = recv(con_fd, buf, BUFSIZ-1, 0);		
		}while(ret < 0 && EINTR == errno);
		if(!ret){
			break;		
		}
		printf("Receive data is :%s",buf);
		if(!strncasecmp(buf,QUIT_STR,sizeof(QUIT_STR))){
			printf("client is exiting\n");
			break;
		}
		bzero(buf, BUFSIZ);
		strcpy(buf,"server received!");
		do{
			ret = send(con_fd, buf, strlen(buf), 0);
		}while(ret < 0 && EINTR == errno);
	}
	close(con_fd);
	close(fd);
	return 0;	
}
















