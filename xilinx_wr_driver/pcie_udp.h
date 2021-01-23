/////////udp
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <errno.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <string.h>  
#include <pcap.h>

#define SERVER_PORT 9996
#define LEN_OF_LISTEN_QUEUE 100
#define BUFFER_SIZE 4096
#define MAX_SIZE 4096
//#define OpenVpnConfig_PATH "log.dat"


void server(int sock);
void* recv_func(void *);
void* send_func(void *);
  
int sock;  
struct sockaddr_in servaddr;  

//2、定义socket  
struct sockaddr_in peeraddr;  
socklen_t peerlen;  
int n; 


////////////////////


////////////pcie
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <unistd.h>
#include <sys/mman.h>

#define MAX 1024*128

int fd_r,fd_s;
char *start_r, *start_s;
//unsigned long offset, size;
//unsigned long bar0_wr;
//unsigned long  value_r,value_w;//, value_bar2;
void pcie_init_r();
void pcie_init_s();

/////pcap
#define MAXBYTE2CAPTURE 2048 
int count = 0;  
pcap_t *descr = NULL;  
char errbuf[PCAP_ERRBUF_SIZE], *device = NULL;  
void processPacket(u_char *arg, const struct pcap_pkthdr *pkthdr, const u_char *packet) ;





