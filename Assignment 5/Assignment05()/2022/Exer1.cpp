#include  <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include  <unistd.h>
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <cstdlib>
#include <csignal>
#include <time.h>
#include <math.h>
#include <chrono>
using namespace std;

using namespace std::chrono;
#define   MAX_COUNT  89
int  main() {
    pid_t  pid;
    int    i;
    int j , pos ;

    high_resolution_clock::time_point start_all=high_resolution_clock::now();
    pid = fork();
    if (pid < 0){
        return -1;
        exit(pid<0);
    }

    high_resolution_clock::time_point stop_process1_msg1;
    duration<double> duration_process1_msg1;
    high_resolution_clock::time_point stop_process2_msg1;
    duration<double> duration_process2_msg1;
    high_resolution_clock::time_point stop_process3_msg1;
    duration<double> duration_process3_msg1;
    high_resolution_clock::time_point stop_process4_msg1;
    duration<double> duration_process4_msg1;

high_resolution_clock::time_point start_process1_msg88_89;
high_resolution_clock::time_point start_process2_msg88_89;
high_resolution_clock::time_point start_process3_msg88_89;
high_resolution_clock::time_point start_process4_msg88_89;

    high_resolution_clock::time_point stop_process1_msg89;
    duration<double> duration_process1_msg89;
    high_resolution_clock::time_point stop_process2_msg89;
    duration<double> duration_process2_msg89;
    high_resolution_clock::time_point stop_process3_msg89;
    duration<double> duration_process3_msg89;
    high_resolution_clock::time_point stop_process4_msg89;
    duration<double> duration_process4_msg89;

    high_resolution_clock::time_point stop_process1_all;
    duration<double> duration_process1;
    high_resolution_clock::time_point stop_process2_all;
    duration<double> duration_process2;
    high_resolution_clock::time_point stop_process3_all;
    duration<double> duration_process3;
    high_resolution_clock::time_point stop_process4_all;
    duration<double> duration_process4;


    duration<double> duration_process1_all;
    duration<double> duration_process2_all;
    duration<double> duration_process3_all;
    duration<double> duration_process4_all;

    for(i=0; i<5; i++){

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
    for (i = 1; i <= MAX_COUNT; i++) {
        if (pid==0){
            printf("process %d, value  %d\n", pos, i);





            if (i==1 && pos==1){
                stop_process1_msg1 = high_resolution_clock::now();
                duration_process1_msg1 =duration_cast<duration<double>>(stop_process1_msg1-start_all);    
            }
            else if (i==1 && pos==2){
                stop_process2_msg1 = high_resolution_clock::now();
                duration_process2_msg1 =duration_cast<duration<double>>(stop_process2_msg1-start_all);    
            } 
            else if (i==1 && pos==3){
                stop_process3_msg1 = high_resolution_clock::now();
                duration_process3_msg1 =duration_cast<duration<double>>(stop_process3_msg1-start_all);    
            }
            else if (i==1 && pos==4){
                stop_process4_msg1 = high_resolution_clock::now();
                duration_process4_msg1 =duration_cast<duration<double>>(stop_process4_msg1-start_all);    
            }

            else if(i==(MAX_COUNT-1) && pos==1){
                start_process1_msg88_89=high_resolution_clock::now();
            }
            else if(i==(MAX_COUNT-1) && pos==2){
                start_process2_msg88_89=high_resolution_clock::now();
            }
            else if(i==(MAX_COUNT-1) && pos==3){
                start_process3_msg88_89=high_resolution_clock::now();
            }
            else if(i==(MAX_COUNT-1) && pos==4){
                start_process4_msg88_89=high_resolution_clock::now();
            }

            else if(i== MAX_COUNT && pos==1){
                stop_process1_msg89=high_resolution_clock::now();
                duration_process1_msg89=duration_cast<duration<double>>(stop_process1_msg89-start_process1_msg88_89);
                duration_process1_all=duration_cast<duration<double>>(stop_process1_msg89-start_all);
            }
            else if(i== MAX_COUNT && pos==2){
                stop_process2_msg89=high_resolution_clock::now();
                duration_process2_msg89=duration_cast<duration<double>>(stop_process2_msg89-start_process2_msg88_89);
                duration_process2_all=duration_cast<duration<double>>(stop_process2_msg89-start_all);

            }
            else if(i== MAX_COUNT && pos==3){
                stop_process3_msg89=high_resolution_clock::now();
                duration_process3_msg89=duration_cast<duration<double>>(stop_process3_msg89-start_process3_msg88_89);
                duration_process3_all=duration_cast<duration<double>>(stop_process3_msg89-start_all);

            }
            else if(i== MAX_COUNT && pos==4){
                stop_process4_msg89=high_resolution_clock::now();
                duration_process4_msg89=duration_cast<duration<double>>(stop_process4_msg89-start_process4_msg88_89);
                duration_process4_all=duration_cast<duration<double>>(stop_process4_msg89-start_all);

            }

        }
    }
    if(pos==1){
    cout<<endl<<"Position for this cout is: "<<pos<<endl;    
    cout <<"Time for first message of Process 1 print execution in seconds is: " <<duration_process1_msg1.count()<<endl;
    cout <<"Time for last message of Process 1 to get printed alone is: "<<duration_process1_msg89.count()<<endl;
    cout <<"Time needed to print all messages of Process 1 since start is: "<<duration_process1_all.count()<<endl;
    }

    if(pos==2){
    cout<<endl<<"Position for this cout is: "<<pos<<endl;
    cout <<"Time for first message of Process 2 print execution in seconds is: " <<duration_process2_msg1.count()<<endl;
    cout <<"Time for last message of Process 2 to get printed alone is: "<<duration_process2_msg89.count()<<endl;
    cout <<"Time needed to print all messages of Process 2 since start is: "<<duration_process2_all.count()<<endl;
    }

    if(pos==3){
    cout<<endl<<"Position for this cout is: "<<pos<<endl;
    cout <<"Time for first message of Process 3 print execution in seconds is: " <<duration_process3_msg1.count()<<endl;
    cout <<"Time for last message of Process 3 to get printed alone is: "<<duration_process3_msg89.count()<<endl;
    cout <<"Time needed to print all messages of Process 3 since start is: "<<duration_process3_all.count()<<endl;
    }

    if(pos==4){
    cout<<endl<<"Position for this cout is: "<<pos<<endl;
    cout <<"Time for first message of Process 4 print execution in seconds is: " <<duration_process4_msg1.count()<<endl;
    cout <<"Time for last message of Process 4 to get printed alone is: "<<duration_process4_msg89.count()<<endl;
    cout <<"Time needed to print all messages of Process 4 since start is: "<<duration_process4_all.count()<<endl;
    }


    return 0;
}