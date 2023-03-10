#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>
#include  <unistd.h>
#include  <sys/wait.h>
#include  <string>
#include  <string.h>
#include  <iostream>

using namespace std;


#define   MAX_COUNT  15
#define   PROC       15

int main()
{
    int  pid;
    int    i,n,a;
    int    j,l,k;
    int p[PROC][2];
    int pos;

    for(i=0; i<PROC; i++){
      if (pipe(p[i])==-1)

        {
            printf("Pipe Failed" );
            return 1;
        }
    }
    pid = fork();
    if (pid < 0){
      return -1;
    }

    for(i=0; i<PROC; i++){
      if((pid!=0)&&(i<PROC)){
      //  pos=0;
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
    if(pos==0)
    {
      kill(pid, SIGKILL);
      return 0;
    }
    else if(pos==1)
    {
      pid=fork();
      if(pid>0)
        pos=0;
    }
  //  cout<<"Process "<< pos <<" is here.\n";

    if(pos==0)
    {
      for(j=1; j<=MAX_COUNT; j++){
        for(k=0; k<PROC; k++)
        {
          close(p[k][0]);
          write(p[k][1], &j, sizeof(j));
          sleep(1);
        }
      }
    }
    else
    {
      for(i=1; i<=MAX_COUNT; i++){

          close(p[pos-1][1]);
          read(p[pos-1][0], &a, sizeof(a));
          printf("process %d value %d\n",pos,a );

        }
    }
    wait(NULL);

}
