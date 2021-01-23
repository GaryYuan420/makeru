#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define bufsize 50

#define PCIE_SPEED_STATUS  0x100
#define PCIE_AVAILABLE_STATUS  0x101
#define PCIE_READ_SPEED  0x102
#define PCIE_READ_AVAILABLE  0x103
int main(int argc, char *argv[])
{
	//调用驱动

	int fd;
	unsigned long  loop_value = 0;
	int j, i = 1;
	fd = open("/dev/pcie_drv", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}
	char buf_write[bufsize];
	char buf_read[bufsize];
	//read(fd, &value, 4);

	//printf("___USER___:  value = %d\n", value);


	//应用程序去控制灯到亮和灭

	while(1)
	{
		/*for(i=0;i<bufsize;i++){
			buf_write[i] = loop_value;
		}
		//value = 0;
		printf("------------write:----------\n");
		write(fd, buf_write,bufsize);
		for(i=0; i<bufsize; i++)
		{
			printf("%d:%x	",i, *(buf_write+ i));
			if (i % 16 == 0 && i != 0)  
				printf("\n");  
		}
		printf("\n");  
		printf("------------read:----------\n");
		read(fd, buf_read, bufsize);
		for(i=0; i<bufsize; i++)
		{
			printf("%d:%x	",i, *(buf_read+ i));
			if (i % 16 == 0 && i != 0)  
				printf("\n"); 
		}
		printf("\n");  
		sleep(1);
		
		loop_value++;*/
		
		
	/*	printf("read\n");
		read(fd, buf_read, bufsize);
		for(i=0; i<19; i++)
		{
			printf("%d:%x	",i, *(buf_read+ i));
		}*/
		ioctl(fd, PCIE_SPEED_STATUS, &i);
		printf("i-S is %d\n",i);
		i++;
		ioctl(fd, PCIE_AVAILABLE_STATUS, &i);
		printf("i-A is %d\n",i);
		i++;
		ioctl(fd, PCIE_READ_SPEED, &j);
		printf("j-S is %d\n",j);
		ioctl(fd, PCIE_READ_AVAILABLE, &j);
		printf("j-A is %d\n",j);
		sleep(1);
		
		
	}


	close(fd);

	return 0;

}



