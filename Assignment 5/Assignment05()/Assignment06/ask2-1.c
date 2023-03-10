#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>

#define   MAX_COUNT  15

int main(int)
{
     pid_t  pid,pid2;
     int    i,pos;

     pid=fork();
     for (i=0; i<3; i++)
     {
	 if (pid==0)
         {
	     pos=i+1;
	     break;
	 }
	 else if ((pid!=0) && (i<2))
	 {
	     pid=fork();
	 }
      }

     if (pos!=1)
     sleep(pos*10);

     for (i = 1; i <= MAX_COUNT; i++) 
     {
	  if (pid==0)
	  {
		printf("Proccess %d message %d\n",pos,i);
		sleep(i*1/7);
	  }
     }
     return 0;
}
