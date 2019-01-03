#include"llstat.h"

int FileStat(char *FileName)
{
	char *week[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	struct stat buf;
	int n;
	struct tm *tp;
	struct passwd *uid_info;
	struct group *gid_info;
	
	if (lstat(FileName, &buf) < 0)
	{
		perror("lstat");
		return -1;
	}

	switch (buf.st_mode & S_IFMT)
	{
		case S_IFREG:
		  printf("-");
		  break;
		case S_IFDIR:
		  printf("d");
		  break;
	}

	for (n=8; n>=0; n--)
	{

	  if (buf.st_mode & (1<<n))
	  {
		 switch (n % 3)
		 {
			case 2:
			   printf("r");
			   break;
			case 1:
			   printf("w");
			   break;
			case 0:
			   printf("x");
			   break;
		 }
	  }
	  else
	  {
		 printf("-");
	  }
	}


	uid_info =getpwuid( buf.st_uid );//找到uid对应的用户
	printf("  %s",uid_info->pw_name);
	gid_info = getgrgid(buf.st_gid );//找到gid对应的组
	printf("  %s",gid_info->gr_name);
	printf(" %lu\t", buf.st_size);
	tp = localtime(&(buf.st_mtime));
	printf(" %s ",week[tp->tm_mon+1]);
	printf(" %02d ", tp->tm_mday);
	printf(" %02d:%02d ", tp->tm_hour,tp->tm_min);
	printf(" %s\n",FileName);

	return 0;
}




