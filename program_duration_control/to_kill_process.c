#include <stdio.h> 
#include "stdlib.h"
#include <string.h>
int main()
{
	FILE *fp;
	char buf[255] = {0};
	if ((fp = _popen("tasklist | find /i \"chrome.exe\"", "r")) == NULL) {
		perror("Fail to popen\n");
		exit(1);
	}
	while (fgets(buf, 255, fp) != NULL) {
        char *revbuf[100] = {0};
        int num = 0;
        split(buf," ",revbuf,&num);
        if (num > 0) {
            char command_prefix[50] = "taskkill /f /t /im ";
            char *to_kill_command = strcat(command_prefix, revbuf[1]);
            printf("to_kill: %s", to_kill_command);
            
            int kill_result = system(to_kill_command);
            if (kill_result > -1) {
                printf("killed: %s", revbuf[1]);
            } else {
                printf("kill: %s failed", revbuf[1]);
            }
        }


        // for (int i = 0;i < num; i ++) {
        //     printf("%s - ",revbuf[i]);
        // }
        printf("\n");
	}

	_pclose(fp);


	return 0;
}

void s() 
{
    char buf[]="hello@boy@this@is@heima";
    char *temp = strtok(buf,"@");
    while(temp)
    {
        printf("%s\n",temp);
        temp = strtok(NULL,"@");
    }
    
    return 0;
}


void split(char *src,const char *separator,char **dest,int *num) {
     char *pNext;
     int count = 0;
     if (src == NULL || strlen(src) == 0)
        return;
     if (separator == NULL || strlen(separator) == 0)
        return;
     pNext = strtok(src,separator);
     while(pNext != NULL) {
          *dest++ = pNext;
          ++count;
         pNext = strtok(NULL,separator);
    }
    *num = count;
}