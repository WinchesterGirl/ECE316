#SERVER


#SERVE
#READ
#WRITE
#CLOSE



#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void serve(int);
#define PORT 8080
#define BUFSIZE 1024
main( int argc, char **argv )
{
printf("hello from server\n");
int lsd; 
struct sockaddr_in sin; 
int sin_size=sizeof(sin);
int sd; 

printf("creating listening socket\n");
lsd=socket(AF_INET, SOCK_STREAM, 0);
if ( lsd == -1 )
{
	fprintf(stderr, "%s: cannot create listening socket: ", argv[0]);
	perror(0);
	exit(1);
}
else{
	printf("%s: created listening socket\n", argv[0]);
}
 
 bzero(&sin, sin_size);

sin.sin_family = AF_INET;
sin.sin_addr.s_addr = htonl(INADDR_ANY);
printf("%s\n", sin.sin_addr.s_addr);
sin.sin_port = htons(PORT);
printf("%d\n", sin.sin_port);


if ( bind(lsd, &sin, sin_size) < 0 )
{
	fprintf(stderr, "%s: cannot bind listening socket: ", argv[0]);
	perror(0);
	exit(1);
}else{
	printf("%s: listening socket binded\n", argv[0]);
}

if ( listen(lsd, 5) <0 )
{
	fprintf(stderr, "%s: cannot listen on socket: ", argv[0]);
	perror(0);
	exit(1);
}else{
	printf("%s: listening on socket\n", argv[0]);
}
if ( (sd=accept(lsd, &sin, &sin_size)) <0){
	fprintf(stderr, "%s: cannot accept connection: ", argv[0]);
	perror(0);
	exit(1);
 }else
 	printf("server acccept the client...\nWaiting for client's message\n");

 serve(sd); 
 

 close(sd); 
}
void serve(int sd){ 
char buff[BUFSIZE]; 
 int n; 

 for (;;) { 
 bzero(buff, BUFSIZE); 
 

 read(sd, buff, sizeof(buff)); 

 printf("From client: %s\t To client : ", buff); 
 bzero(buff, BUFSIZE); 
 n = 0; 

 while ((buff[n++] = getchar()) != '\n') 
 ; 
 

 write(sd, buff, sizeof(buff)); 
 

 if (strncmp("exit", buff, 4) == 0) { 
 printf("Server Exit...\n"); 
 break; 
 } 
 } 
 return;
}

