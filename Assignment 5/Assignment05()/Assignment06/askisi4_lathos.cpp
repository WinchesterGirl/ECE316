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
    int    i,n;
    int    j;
    int p[PROC][2];
    int pos;
    pid = fork();
    if (pid < 0){
      return -1;
    }
    for(i=1; i<=PROC; i++){
      if (pipe(p[i])==-1)

        {
            printf("Pipe Failed" );
            return 1;
        }
    }
    for(i=0; i<PROC; i++){
      if((pid!=0)&&(i<PROC)){
        //pos=0;
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
        exit(0);

      for (i = 1; i <= MAX_COUNT; i++) {
        if (pid > 0){

          for(int l=1; l<=PROC; l++)
          {
            close(p[1][0]);
            write(p[1][1], &n, sizeof(n));
            wait(NULL);
            close(p[PROC][1]);
            read(p[PROC][0], &n, sizeof(n));
          }

            /*close(p[1][0]);
            write(p[1][1], &n, sizeof(n));
            close(p[PROC][1]);
            read(p[PROC][0], &n, sizeof(n));
            */

        }
      }
      for (i = 1; i <= MAX_COUNT; i++) {
        if(pid==0){
          //sleep(pos);
          for(int l=1; l<=PROC; l++)
          {
          cout<<"Possition "<<pos<<" is waiting.\n";
          wait(NULL);

          close(p[pos][1]);
          while(read(p[pos][0], &n, sizeof(n))==-1);
          //  open(p[pos][1]);
        //  close(p[pos][1]);
          //read(p[pos][0], &n, sizeof(n));
          //cout<<"Possition "<<pos<<" is conyinuing.\n";
          //sleep(pos+i);
          printf("process %d value %d\n",pos,i );

          close(p[pos+1][0]);
          while(write(p[pos+1][1], &n, sizeof(n))==-1);
          //  open(p[pos][0]);
          //close(p[pos][0]);
          //write(p[pos+1][1], &n, sizeof(n));
          cout<<"Possition "<<pos<<" is exiting.\n";
        }

      }

      }
      wait(NULL);
    /*

      //sleep(pos);
      if (pid > 0){
        for (i = 1; i <= MAX_COUNT; i++) {

  			close(p[0][0]);// Close reading end of first pipe
  			// Write input string and close writing end of first
        			// pipe.
  			//n=1;
          		write(p[0][1], &n, sizeof(n));
          		//close(p1[1]);
  			//wait(NULL);
        close(p[PROC-1][1]);

        read(p[PROC-1][0], &n, sizeof(n));


  		}
    }
    else if(pid==0){
      for(j=0; j<PROC-1; j++){
          for (i = 1; i <= MAX_COUNT; i++) {
                //sleep(i);
              	close(p[j][0]);
                read(p[j][1], &n, sizeof(n));
                //sleep(pos+i);
                printf("process %d value %d\n",pos,i );
                close(p[j+1][1]);
                write(p[j+1][0], &n, sizeof(n));

          }
      }


    }*/


}

