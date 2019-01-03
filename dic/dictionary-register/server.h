#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <sqlite3.h>
#include <time.h>



#define   N  32

#define  R  1   // user - register
#define  L  2   // user - login
#define  Q  3   // user - query
#define  H  4   // user - history

#define _DEBUG_ 1
#if _DEBUG_
#define PR(...) printf(__VA_ARGS__)
#else
#define PR(...) 
#endif

#define  DATABASE  "dic.db"
#define USRTABLE	"usr"


// 定义通信双方的信息结构体
struct msg{
	int type;
	char name[N];
	char data[256];
};

void handler (void *arg, sqlite3 *db);
void sig_child_handle(int signo);

int do_register(int socketfd, struct msg* dicmsg, sqlite3 * db);
int do_login(int socketfd, struct msg* dicmsg, sqlite3 * db);

int get_time(char *time);

//int do_register(int socketfd,  struct msg *dicmsg);
//int do_login(int socketfd, struct msg *dicmsg);
//int do_search(int socketfd, struct msg *dicmsg);
//int do_query(int socketfd, struct msg *dicmsg);
//int do_history(int socketfd, struct msg *dicmsg);





