#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main()
{
    pid_t child_a,child_b,child_c;
    int x;
    int fd_a[2],fd_b[2],fd_c[2],i;

    pipe(fd_b);
    pipe(fd_a);
    pipe(fd_c);


    if (child_b = fork() == 0)
    {
        for ( i=0; i < 51; i++)
        {
            close(fd_b[1]);
            read(fd_b[0], &x, sizeof(x));
            cout << "child process 2, message = " << i+1 << " " << endl;
            close(fd_a[0]);
            write(fd_a[1], &x, sizeof(x));

        }
        exit(0);
    }
    else if (child_a = fork() == 0)
    {
        for ( i=0; i < 51; i++)
        {
            close(fd_a[1]);
            read(fd_a[0], &x, sizeof(x));
            cout << "child process 1, message = " << i+1 << " " << endl;
            close(fd_c[0]);
            write(fd_c[1], &x, sizeof(x));
        }
        exit(0);
    }
    else if (child_c = fork() == 0)
    {
        for ( i=0; i < 51; i++)
        {
            close(fd_c[1]);
            read(fd_c[0], &x, sizeof(x));
            cout << "child process 3, message = " << i+1 << " " << endl;
            close(fd_b[0]);
            write(fd_b[1], &x, sizeof(x));

        }
        exit(0);
    }
    else
    {
        close(fd_b[0]);
        write(fd_b[1],&x,sizeof(x));
    }


cout << "TELOS " << endl;
}

