#CLIENT 


#READ
#WRITE
#CLOSE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define BUFSIZE 1024
#define SERVER_PORT 8080
void func(int sockfd) 
{ 
 char buff[BUFSIZE]; 
 int n; 
 for (;;) { 
 bzero(buff, sizeof(buff)); 
 printf("Enter the string : "); 
 n = 0; 
 while ((buff[n++] = getchar()) != '\n') 
 ; 
 write(sockfd, buff, sizeof(buff)); 
 bzero(buff, sizeof(buff)); 
 read(sockfd, buff, sizeof(buff)); 
 printf("From Server : %s", buff); 
 if ((strncmp(buff, "exit", 4)) == 0) { 
 printf("Client Exit...\n"); 
 break; 
 } 
 }
 return;
} 
main( int argc, char **argv )
{
printf("hello from client\n");
int sd; 
struct sockaddr_in server; 
struct hostent *server_host; 
char buf[BUFSIZE];
int nbytes;
/* Create socket */
sd=socket(AF_INET, SOCK_STREAM, 0);
if ( sd == -1 ) {
	fprintf(stderr, "%s: cannot create socket: ", argv[0]);perror(0);
	exit(1);
}else
 printf("Socket successfully created..\n"); 
 bzero(&server, sizeof(server)); 

server.sin_family = AF_INET;
server.sin_addr.s_addr = inet_addr("127.0.0.1");
server.sin_port = htons(SERVER_PORT);

if ( connect(sd, &server, sizeof(server)) < 0 ) {
fprintf(stderr, "%s: cannot connect to server: ", argv[0]);
perror(0);
exit(1);
}

 func(sd); 
 
 
 close(sd); 
}
