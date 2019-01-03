#include <stdio.h>
#include <string.h>

#define  N  64

int main(int argc,  char *argv[])
{
   FILE *fp;
   int line = 0;
   char buf[N];

   if (argc < 2) {
      printf("Usage: %s <file>\n", argv[0]);
	  return -1;
   }
   
   if ((fp = fopen(argv[1], "r")) == NULL) {
      printf("fopen  error\n");
      return -1;
   }
   
   while (fgets(buf, N, fp) != NULL) {
      if (buf[strlen(buf)-1] == '\n')
		line++;
   }

   printf("the line of %s is %d\n", argv[1], line);
   
   return  0;
 }
