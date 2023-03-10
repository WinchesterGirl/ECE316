#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include  <unistd.h>
#include  <sys/wait.h>
#include  <string>
#include  <string.h>

using namespace std;


#define   MAX_COUNT  15

int  main()
{
    	int  pid;
    int    i;
	  int j,pos;
 	  int p1[2];
	  int p2[2];
	  int p3[2];
	  int p4[2];
	  int n;

    char pro1[]="process 1 value ";
    char pro2[]="process 2 value ";
    char pro3[]="process 3 value ";
    char minima[100] ;
    int size;

   	if (pipe(p1)==-1)

    	{
        	printf("Pipe Failed" );
        	return 1;
    	}
    	if (pipe(p2)==-1)
    	{
        	printf("Pipe Failed" );
        	return 1;
    	}
	if (pipe(p3)==-1)

    	{
        	printf("Pipe Failed" );
        	return 1;
    	}
	if (pipe(p4)==-1)

    	{
        	printf("Pipe Failed" );
        	return 1;
    	}

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
		if (pid > 0){
      for (i = 1; i <= MAX_COUNT; i++) {
			     close(p1[0]);
    	      write(p1[1], &pro1, sizeof(pro1));
            close(p4[1]);
            read(p4[0], &n, sizeof(n));
		}
  }
		else if (pid==0){
			if(pos==1){
			     for (i = 1; i <= MAX_COUNT; i++) {
				        close(p1[1]);
				        read(p1[0], &minima, 100);
				        printf("%s %d\n" ,minima,i);
				        close(p3[0]);
				        write(p3[1], &pro3, sizeof(pro3));
			     }
			}else if(pos==3){
			     for (i = 1; i <= MAX_COUNT; i++) {
								close(p3[1]);
		            read(p3[0], minima, 100);
			          printf("%s %d\n" ,minima,i);
				        close(p2[0]);
                write(p2[1], &pro2, sizeof(pro2));
			      }
			}else if(pos==2){
			     for (i = 1; i <= MAX_COUNT; i++) {
				      close(p2[1]);
              read(p2[0], minima, 100);
				      printf("%s %d\n" ,minima,i);
				      close(p4[0]);
				      write(p4[1], &n, sizeof(n));
			      }
        }
     }
     wait(NULL);
}
