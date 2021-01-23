#include"pcie_udp.h" 


int main(void){  

    /* Get the name of the first device suitable for capture */  
    device = "eth0";  
    printf("FUNC %s\n",  __FUNCTION__);  
  
    /* Open device in promiscuous mode */  
	
	pthread_t rec_id;
	if(pthread_create(&rec_id, NULL, recv_func, (void*)&sock) != 0)
	{
		perror("pthread_create function failed:1");
	}
	pthread_t send_id;
	if(pthread_create(&send_id, NULL, send_func, (void*)&sock) != 0)
	{
		perror("pthread_create function failed:2");
	}
	while(1)
		sleep(1);
	return 0;  
} 


////////////////////////////////////////////pcap///////////////////////////////////////
void* recv_func(void * arg)
{  
	long int counter = 0;
	long int j , bar0_data , offset , size;
	int i;
	char *bar1_data_write;
	size = 100;
	bar1_data_write = (char *)malloc(size); 
	pcie_init_r();
	while(1){
		

		for(i=0; i<size; i++)
		{
			*(bar1_data_write + i) = i % 4 ;
		}
		
		write(fd_r, bar1_data_write, size);

		counter++;
		sleep(1);
	} 
	close(fd_r);
	free(bar1_data_write);
   return 0;  
} 




void* send_func(void * arg)
{
	pthread_detach(pthread_self());
	int len;
	unsigned long int  offset, size;
	// int sock = (int*)arg;
	unsigned long bar0_read;
	unsigned int i = 0;
	int ret;
	
	char *bar1_data_read;
	bar1_data_read = (char *)malloc(1536); 
	pcie_init_s();
	while(1){
		ret=read(fd_s, bar1_data_read, 4);
		if(ret!=0){
			usleep(20*1000);
			//close(fd_s);
			continue;
		}
		
		offset = *(bar1_data_read + 3) << 8 + *(bar1_data_read + 2);
		size = (*(bar1_data_read + 1) << 8) | *(bar1_data_read);
		printf("offset: %lx , size: %lx\n",offset , size);
		for(i=0; i<size; i++)
		{
			printf("%x\t",*(bar1_data_read + 4 + i));
			
			if(i % 16 == 0 && i != 0)
				printf("\n");
		}
					printf("\n");
		//usleep(20*1000);
	}
		close(fd_s);
		free(bar1_data_read);
	/////////////////////////////////////////////////////////
   pthread_exit(NULL);
}


void pcie_init_r()
{
	fd_r = open("/dev/pcie_drv", O_RDWR);
	if(fd_r < 0)
	{
		perror("open");
		exit(1);
	}
}


void pcie_init_s()
{
	fd_s = open("/dev/pcie_drv", O_RDWR);
	if(fd_s < 0)
	{
		perror("open");
		exit(1);
	}
}



