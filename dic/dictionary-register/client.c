#include "client.h"
int main(int argc, char *argv[])
{
	struct msg dicmsg;
	int socketfd;
	struct sockaddr_in serveraddr;
	int selc;
	if(argc != 3){
		printf("USAGE:%s <serverip> <port>", argv[1]);
		return -1;
	}

	if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		return -1;
	}

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));

	if(connect(socketfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0){
		perror("connect");
		return(-1);
	}
	while(1){
		printf("*****************************************************************\n");
		printf("* 1.register          2.login              3.quit               *\n");
		printf("*****************************************************************\n");
		printf("Please choose:");

		scanf("%d", &selc);
		getchar();

		switch (selc){
			case 1:
				do_register(socketfd, &dicmsg);
				break;
			case 2:
				if(do_login(socketfd, &dicmsg) == 1){
					do_search(socketfd, &dicmsg);
				}
				break;
			case 3:
				close(socketfd);
				exit(0);
				break;
			default:
				printf("wrong cmd\n");
			}
	}
	return 0;
}

int do_register(int socketfd, struct msg *dicmsg)
{

	dicmsg->type = R;
	printf("Input name:");
	scanf("%s", dicmsg->name);
	getchar();

	printf("Input passwd:");
	scanf("%s", dicmsg->data);
	PR("type:%d, name:%s,data:%s\n",dicmsg->type,dicmsg->name,dicmsg->data);
	if(send(socketfd, dicmsg, sizeof(struct msg), 0) < 0){
		printf("fail to send.\n");
		return -1;
	}

	if(recv(socketfd, dicmsg, sizeof(struct msg), 0) < 0){
		printf("Fail to recv.\n");
		return -1;
	}

	printf("%s\n", dicmsg->data);

	return 0;
	
}

int do_login(int socketfd, struct msg *dicmsg)
{
	dicmsg->type = L;
	printf("Input name:");
	scanf("%s", dicmsg->name);
	getchar();

	printf("Input passwd:");
	scanf("%s", dicmsg->data);
	if(send(socketfd, dicmsg, sizeof(struct msg), 0) < 0){
		printf("fail to send.\n");
		return -1;
	}

	if(recv(socketfd, dicmsg, sizeof(struct msg), 0) < 0){
		printf("Fail to recv.\n");
		return -1;
	}

	if(strncmp(dicmsg->data, "OK", 3) == 0){
		printf("Login ok!\n");
		return 1;
	}else {
		printf("%s\n", dicmsg->data);
	}
	return 0;
}

int do_search(int socketfd, struct msg *dicmsg)
{
	int selc;
	
	

	
	while(1){
		printf("*****************************************************************\n");
		printf("* 1.query          2.history              3.quit               *\n");
		printf("*****************************************************************\n");
		printf("Please choose:");
		scanf("%d", &selc);
		getchar();
		switch (selc){
			case 1:
				do_query(socketfd, dicmsg);
				break;
			case 2:
				do_history(socketfd, dicmsg);
				break;
			case 3:
				close(socketfd);
				exit(0);
				break;
			default:
				printf("wrong cmd\n");
			}
	}
	
	return 0;
		
}

int do_query(int socketfd, struct msg *dicmsg)
{
	dicmsg->type = Q;
	puts("--------query word,input # to back------");

	while(1)
	{
		printf("Input word:");
		scanf("%s", dicmsg->data);
		PR("%s\n", dicmsg->data);
		getchar();
		if(strncmp(dicmsg->data, "#", 1) == 0)
			break;

		if(send(socketfd, dicmsg, sizeof(struct msg), 0) < 0)
		{
			printf("Fail to send.\n");
			return -1;
		}

		if(recv(socketfd, dicmsg, sizeof(struct msg), 0) < 0)
		{
			printf("Fail to recv.\n");
			return -1;
		}
		printf("%s\n", dicmsg->data);
	}
		
	return 0;
}

int do_history(int socketfd, struct msg *dicmsg)
{
	dicmsg->type = H;

	if(send(socketfd, dicmsg, sizeof(struct msg), 0) < 0)
	{
		printf("Fail to send.\n");
		return -1;
	}
	
	while(1)
	{
		if(recv(socketfd, dicmsg, sizeof(struct msg), 0) < 0)
		{
			printf("Fail to recv.\n");
			return -1;
		}

		if(dicmsg->data[0] == '\0')
			break;
		printf("%s\n", dicmsg->data);
	}

	return 0;
}

