#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include  <unistd.h>
#include  <sys/wait.h>


#define   MAX_COUNT  15
#define   BUF_SIZE   100

int  main()
{
    	int  pid;
    	int    i;
     	//char   buf[BUF_SIZE];
	int j,pos;
 	int p1[2];
	int p2[2];
	int p3[2];
	int p4[2];
	int n; 
   	if (pipe(p1)==-1)

    	{
        	fprintf(stderr, "Pipe Failed" );
        	return 1;
    	}
    	if (pipe(p2)==-1)
    	{
        	fprintf(stderr, "Pipe Failed" );
        	return 1;
    	}
	if (pipe(p3)==-1)

    	{
        	fprintf(stderr, "Pipe Failed" );
        	return 1;
    	}
	if (pipe(p4)==-1)

    	{
        	fprintf(stderr, "Pipe Failed" );
        	return 1;
    	}


     	//fork();
     	pid = fork();
	if (pid < 0){
		return -1;
	}
	for(i=0; i<3; i++){
		if((pid!=0)&&(i<2)){
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


		//printf("%d\n", i);
		if (pid > 0){
			close(p1[0]);// Close reading end of first pipe
			// Write input string and close writing end of first
      			// pipe.
			//n=1;
        		write(p1[1], &n, sizeof(n));
        		//close(p1[1]);
			//wait(NULL);


		}
		else if (pid==0){
          		//printf("This line is from pid %d, value = %d\n", pos, i);
          		//write(1, buf, strlen(buf));
			/*close(p1[1]);

			read(p1[0], &n, sizeof(n));
			close(p1[0]);*/

			if(pos==1){
			for (i = 1; i <= MAX_COUNT; i++) {
				//wait(NULL);
				close(p1[1]);

				read(p1[0], &n, sizeof(n));
				//close(p1[0]);

				printf("This line is from pid %d, value %d\n",pos,i);
				//n=3;
				close(p3[0]);
				write(p3[1], &n, sizeof(n));

				//wait(NULL);
			}
			}else if(pos==3){
			for (i = 1; i <= MAX_COUNT; i++) {
				//wait(NULL);
				close(p3[1]);

				read(p3[0], &n, sizeof(n));
				//close(p3[0]);

				printf("This line is from pid %d, value %d\n",pos,i);
				//n=2;
				close(p2[0]);
				write(p2[1], &n, sizeof(n));

				//wait(NULL);
			}
			}else if(pos==2){
			for (i = 1; i <= MAX_COUNT; i++) {
				//wait(NULL);
				close(p2[1]);

				read(p2[0], &n, sizeof(n));
				//close(p3[0]);

				printf("This line is from pid %d, value %d\n",pos,i);
				//n=1;
				close(p1[0]);
				write(p1[1], &n, sizeof(n));
        			//wait(NULL);
			}




		}
     	}
}
