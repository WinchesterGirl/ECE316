#include  <stdio.h>
#include  <string.h>
#include  <unistd.h>
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <cstdlib>
#include <csignal>

using namespace std;
#define   MAX_COUNT  15

int  main()
{
    	pid_t  pid;
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


    	for (i = 1; i <= MAX_COUNT; i++) {
		if (pid==0){
          		printf("process %d, value  %d\n", pos, i);
		}
     	}
}
