#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <sys/wait.h>
#include <sys/signal.h>

using namespace std;

int j=1;
char* pid;

void sig_handler(int signal){

    if (signal == SIGCONT){
    cout << endl << "Process " << pid << " is executing." << endl << endl;
    j=0;
    }
    else if (signal == SIGTSTP){
    cout << endl << "Process " << pid << " is suspended." << endl << endl;
    j=1;
    }
}

 int main(int argc, char *argv[])
  {

     signal(SIGTSTP,sig_handler);
     signal(SIGCONT,sig_handler);
     pid = argv[1];
     int i=1;

     while(1){
        while(j==0){
            cout << "Program: " << argv[2] << " messages printed: " << i << endl;
            usleep(500000);
            i++;
        }
    }
  return 0;
}
