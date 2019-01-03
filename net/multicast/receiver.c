#include "net.h"

int main (int argc, char* argv[])
{
	int fd = -1;
	struct sockaddr_in sin;
	struct ip_mreq mreq;
	if(argc < 3){
		printf("Usage: %s <ip> <port>\n",argv[0]);
		exit(1);
	}
	/* 1. 创建socket fd */
	if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) < 0) {	//udp程序
		perror ("socket");
		exit (1);
	}

	/* 2. 允许绑定地址快速重用 */
	int b_reuse = 1;
	setsockopt (fd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof (int));

	bzero(&mreq, sizeof(mreq));
	mreq.imr_multiaddr.s_addr = inet_addr(argv[1]);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	if(setsockopt(fd, IPPROTO_IP,
			IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0){
		perror("setsocketopt");
		exit(1);
	}

	/*2. 绑定 */
	/*2.1 填充struct sockaddr_in结构体变量 */
	bzero (&sin, sizeof (sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons (atoi(argv[2]));	//网络字节序的端口号

	/* 让服务器程序能绑定在任意的IP上 */
	sin.sin_addr.s_addr = htonl (INADDR_ANY);

	/*2.2 绑定 */
	if (bind (fd, (struct sockaddr *) &sin, sizeof (sin)) < 0) {
		perror ("bind");
		exit (1);
	}

	char buf[BUFSIZ];
	struct sockaddr_in cin;
	socklen_t addrlen = sizeof (cin);
	printf ("\nUDP server started!\n");
	while (1) {
		bzero (buf, BUFSIZ);
		recvfrom(fd, buf, BUFSIZ, 0, (struct sockaddr*)&cin, &addrlen);
		printf("receive[%s:%d]:%s\n",inet_ntoa(cin.sin_addr),
				ntohs(cin.sin_port),buf);
		if( !strncasecmp(buf, QUIT_STR, strlen(QUIT_STR))) {  //用户输入了quit字符
                        printf("Client is exited!\n");
          }
	}

	close (fd);

	return 0;
}
