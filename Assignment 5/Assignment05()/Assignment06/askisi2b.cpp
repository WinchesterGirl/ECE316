#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include  <unistd.h>

#define   MAX_COUNT  15

int  main()
{
    	int  pid;
    	int    i;
     	int j,pos;

     	pid = fork();
	if (pid < 0){
		return -1;
	}
	for(i=0; i<3; i++){
		if((pid!=0)&&(i<2)){
			pid = fork();

			if (pid < 0){
				return -1;
			}
		}
		else if(pid==0){
			pos=i+1;
			break;

		}

	}
		sleep(pos);
    	for (i = 1; i <= MAX_COUNT; i++) {
          if (pid==0){
          		printf("process %d, value  %d\n", pos, i);
		          }
     	}
}
