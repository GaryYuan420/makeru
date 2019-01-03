#include <stdio.h>
#include <stdlib.h>


void fun1(char * s){printf("fun1:%s\n",s);}
void fun_call(void (*fp)(char * s), char * s);//定义回调函数

int main(int argc, char* argv[])
{
	if(argc < 2){
		printf("Usage: %s <string>\n",argv[0]);
		exit(-1);
	}
	fun_call(fun1,argv[1]);//调用回调函数
	return 0;
}

void fun_call(void (*fp)(char * s), char * s)
{
	fp(s);//调用fun1
}
