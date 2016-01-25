#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    FILE *fp=fopen("tutoraccounts.txt","r");
    char tmp[256];
    strcpy(tmp,"hello");
    while(fp!=NULL && fgets(tmp, sizeof(tmp), fp)!=NULL)
    {
        if (strstr(tmp, "word1")) {
            printf("%s", tmp);
	} else if (strstr(tmp, "word2")) {
            printf("%s", tmp);
	}
    }
    if(fp!=NULL) fclose(fp);
    return 0;
}

