#include"net.h"

int main(int argc, char* argv[])
{
	int fd = -1;
	struct sockaddr_in sin;
	int i;
	int err;
	int fd_all[FD_SETSIZE];
	
	fd_set fd_store;
	fd_set fd_select;

	struct timeval timeout;
	struct timeval timeout_select;

	int con_fd = -1;
	struct sockaddr_in cin;
	socklen_t addrlen = sizeof(cin);
	char client_addr[16];

	int ret = -1;
	char buf[BUFSIZ];
	//配置超时时间
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;

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
	memset(fd_all, -1, sizeof(fd_all));
	fd_all[0] = fd;
	FD_ZERO(&fd_store);
	FD_SET(fd, &fd_store);//将监听套接字加入fd_read
	int maxfd = fd_all[0];//初始fd中只有socket套接字

	while(1){
		fd_select = fd_store;//select会改变值，每次重新赋值
		timeout_select = timeout;

		err = select(maxfd+1, &fd_select, NULL, NULL, &timeout_select);
		if(err < 0){
			perror("select");
			exit(1);
		}
		if(err == 0){
			printf("timeout!\n");
		}

		//监听套接字
		if(FD_ISSET(fd, &fd_select)){//有新的连接
			if((con_fd = accept(fd, (struct sockaddr *)&cin, &addrlen)) < 0){
				perror("accept");
				exit(1);	
			}
			printf("accept!\n");
			if(!inet_ntop(AF_INET, (void *)&cin.sin_addr, client_addr, sizeof(client_addr)) < 0){
				perror("inet_pton");
				exit(1);	
			}
			printf("client is %s:%d\n",client_addr,ntohs(cin.sin_port));
			for(i=0; i<FD_SETSIZE; i++){
				if(fd_all[i] != -1){
					continue;
				}else{
					fd_all[i] = con_fd;
					printf("client fd_all[%d] join\n",i);
					break;
				}
			}
			FD_SET(con_fd, &fd_store);
			if(maxfd < con_fd){
				maxfd = con_fd;
			}
		}

		//查看连接套接字是否可读
		for(i=1; i < maxfd; i++){
			if(FD_ISSET(fd_all[i], &fd_select)){
				printf("fd_all[%d] is ok\n",i);
				bzero(buf,BUFSIZ);
				do{
					ret = recv(fd_all[i], buf, BUFSIZ-1, 0);		
				}while(ret < 0 && EINTR == errno);
				if(!ret){
					printf("client:fd_all[%d] exit\n",i);
					FD_CLR(fd_all[i], &fd_store);
					close(fd_all[i]);
					fd_all[i] = -1;
					continue;		
				}
				printf("Receive data is :%s",buf);
				if(!strncasecmp(buf,QUIT_STR,sizeof(QUIT_STR))){
					printf("client is exiting\n");
					continue;
				}
				bzero(buf, BUFSIZ);
				strcpy(buf,"server received!");
				do{
					ret = send(fd_all[i], buf, strlen(buf), 0);
				}while(ret < 0 && EINTR == errno);
			}
		}

	}
	close(fd);
	return 0;	
}
















