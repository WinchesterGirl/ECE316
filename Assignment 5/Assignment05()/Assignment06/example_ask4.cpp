#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <csignal>
#define NUM 6

using namespace std;
int main()
{

int value,i;

pid_t pid[NUM];
int pfd[NUM][2];

for (i = 0; i < NUM; ++i)
	{

    	if (pipe(pfd[i]) < 0)
		{
       		perror("pipe");
       		exit(1);
    		}
	}

for (i = 0; i < NUM; ++i)
	{
    	pid[i] = fork();

    if (pid[i] == 0)
		{
				close(pfd[i][1]);

        while (read(pfd[i][0], &value, sizeof(value)) == sizeof(value))
					cout << "Process: " << i+1 << "  message: " << value << endl;

				//cout<<"Process "<< i+1<< " exiting\n";
       	//return 0;
    }
    else
		{
			cout<<"KOPELOUI\n";
			continue;
		}


	}

    for(value=0;value<=5;++value)
    {

        for(i=0;i<NUM;++i)
        {
            close(pfd[i][0]);
            if (write(pfd[i][1], &value, sizeof(value)) != sizeof(value))
            {
                cout << "Eggrafi " << i << endl;
                exit(1);
            }

            sleep(1);
        }

  }

  for(i=0;i<NUM;++i)
      kill(pid[i], SIGKILL);


}
