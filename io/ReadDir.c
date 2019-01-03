#include"llstat.h"

int  main(int argc, char *argv[]) {

    DIR *dirp;
    struct dirent *dp;
	
    if ((dirp  = opendir(".")) == NULL) {  //打开当前文件夹
           perror("opendir");  
		   return -1;
    }
    while ((dp = readdir(dirp)) != NULL) {
		FileStat( dp->d_name);
    }
    closedir(dirp);

	return 0;
}
