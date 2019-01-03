#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main()
{
   FILE *fp;
   time_t t;
   struct tm *tp;
   
   if ((fp = fopen("test.txt", "a+")) == NULL) {
       perror("fopen");
       return -1;
   }
  
   while ( 1 )
   {
      time(&t);
      tp = localtime(&t);
      fprintf(fp, "%d-%02d-%02d %02d:%02d:%02d\n", tp->tm_year+1900, tp->tm_mon+1,
                                tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
      fflush(fp);
      sleep(1);
   }	  
	fclose(fp);
   return  0;
 }
