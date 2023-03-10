#include  <stdio.h>
#include  <string.h>
#include  <stdlib.h>
#include  <sys/types.h>

#define   MAX_COUNT  30

int  main()
{
     pid_t  pid;
     int    i,pos;

     if ((pid=fork()) < 0)
     exit(1);     

     for (i=0; i<3; i++)
     {
	 if (pid==0)
         {
	     pos=i+1;
	     break;
	 }
	 else if ((pid!=0) && (i<2))
	 {
	     if ((pid=fork()) < 0)
             exit(1);
	 }
      }

     for (i = 1; i <= MAX_COUNT; i++) 
     {
	  if (pid==0)
	  {
		printf("Proccess %d message %d\n",pos,i);
	  }
     }
     return 0;
}
