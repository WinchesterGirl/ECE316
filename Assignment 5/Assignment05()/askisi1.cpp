#include  <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include  <unistd.h>
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <csignal>

using namespace std;
#define   MAX_COUNT  89

int  main()
{
    	pid_t  pid;
    	int    i;
	     int j,pos;
    double time[4][3];
    double t1,t2,t3;
    clock_t end1,end2,end3;
     	pid = fork();
	if (pid < 0){
		return -1;
	}
	for(i=0; i<4; i++){
		if((pid!=0)&&(i<3)){
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

        clock_t begin = clock();
    	for (i = 0; i <= MAX_COUNT; i++) {
		if (pid==0){
          		printf("process %d, value  %d\n", pos, i+1);
            if (i==0){
                clock_t end1 = clock();
                double time_spent = (double)(end1-begin);
                t3=time_spent;
            }
            if (i==88){
                clock_t end3 = clock();
                double time_spent3 = (double)(end3-begin);
                t1=time_spent3;
            }
            if (i==89){
                clock_t end2 = clock();
                double time_spent2 = (double)(end2-begin);
                t2=time_spent2;
            }


        }

        }
    clock_t endf = clock();

        double time_spentf = (double)(endf-begin);
        time[pos-1][0]=t3*pow(10,-3);
        time[pos-1][1]=(t2 - t1)*pow(10,-3);
        time[pos-1][2]=time_spentf*pow(10,-3);
    printf("\nProcess %d: %ld/%ld/%ld\n",pos,end1,end2,endf);
}



