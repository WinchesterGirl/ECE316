#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/signal.h>

using namespace std;

float qt;
int k,j,i;
float total_time=0;
float pass_time=0;
int timein_cpu[6]= {0,0,0,0,0,0};
int mintime=10000;

void stp_handler(int signal){
}
void con_handler(int signal){
}

int main(int argc, char *argv[])
{
     int p=2;
     int s=3;
     int e=4;
     int count=0;

     signal(SIGTSTP,stp_handler);
     signal(SIGCONT,con_handler);
     int start_time[(argc-2)/3];
	float current_time;
     float execution_time[(argc-2)/3];
     char *path_process[(argc-2)/3];
     float remaining_time[(argc-2)/3];
     timeval time;
     int start,end;


     if (argc < 2)
        {
        cout<<"You didn't enter any arguments" << endl;
        exit(0);
        }
    else{
        qt = stof(argv[1]);
        while (count < ((argc-2)/3) ){
            path_process[count] = argv[p];
            start_time[count] = atoi(argv[s]);
            execution_time[count] = atoi(argv[e]);
            remaining_time[count] = execution_time[count];
            total_time = total_time + execution_time[count];
            cout << path_process[count] << " " << start_time[count] << " " << execution_time[count] << endl;
            p+=3;
            s+=3;
            e+=3;
            count++;
        }
    }
        i=0;
        pid_t pid[count];

    while(i<count){
         pid_t par,child;
         child=fork();

         if (child==0){
            par = getppid();
            cout << "Child pid: " << i << " " << getpid() << endl << "Parent pid: " << par << endl;
            char num[100]={0x0};
            sprintf(num,"%d",i+1);
            char pi[100]={0x0};
            sprintf(pi,"%d",getpid());
            execl(path_process[i],path_process[i],pi,num,(char*)0);
            exit(0);
         }

         else{
            sleep(1);
            pid[i] = child;
            i++;
         }
    }

    i=0;
    cout << endl << "Processes time: " << total_time << endl << endl;
    gettimeofday(&time,NULL);
    start = time.tv_sec;


    while(pass_time<total_time){
        for(j=0;j<count;j++){

            if (pass_time<start_time[j]){
                continue;
            }
            else if (remaining_time[j]<=0){
                continue;
            }
            else if (remaining_time[j]>= qt && timein_cpu[j]<=mintime){
                
                kill(pid[j],SIGCONT);
                usleep(qt*500000);
                kill(pid[j],SIGTSTP);
                pass_time = pass_time + qt;
                remaining_time[j]=remaining_time[j]-qt;
                timein_cpu[j]+=qt;
                mintime=timein_cpu[j];
                i++;
            }
            else if (timein_cpu[j]<=mintime){
                kill(pid[j],SIGCONT);
                usleep(remaining_time[j]*500000);
                kill(pid[j],SIGTSTP);
                pass_time = pass_time + remaining_time[j];
                remaining_time[j]=0;
                mintime=timein_cpu[j]+qt;
                timein_cpu[j]=10000;
                j++;
            }
            else{
                continue;
            }
        }
    }

    sleep(1);
    gettimeofday(&time,NULL);
    end = time.tv_sec;
    cout << "Scheduler time: " << end - start << endl;
    for(i=0;i<count;i++)
        kill(pid[i],SIGKILL);

    return 0;
}
