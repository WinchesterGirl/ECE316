#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define SERVER_PORT 4610

typedef struct packet{
    char data[1024];
}Packet;

typedef struct frame{
    int frame_kind; //ACK:0, SEQ:1 FIN:2
    int sq_no;
    int ack;
    int sequence;
    Packet packet;
}Frame;

int main(int argc, char **argv[]){
    

	int port = SERVER_PORT;
	int sockfd;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	socklen_t addr_size;

	int frame_id = 0;
	Frame frame_send;
	Frame frame_recv;
	int ack_recv = 1;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");


    while(1){
        printf("Enter Data: ");
        scanf("%s", buffer);
        
        for(int i=0;i<strlen(buffer);i++){
            
            if(ack_recv == 1){
			frame_send.sq_no = frame_id;
			frame_send.frame_kind = 1;
			frame_send.ack = 0;		
            frame_send.sequence=i%2;

            //char Frame[2]={i+'0',buffer[i]};
			//printf("Frame: %c", buffer[i]);
			//strcpy(frame_send.packet.data, buffer[i]);
            frame_send.packet.data[0]=buffer[i];
            printf("[+]Frame %d Send: %c\n",  frame_send.sequence,frame_send.packet.data[0]);
			sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
			//printf("[+]Frame Send\n");
            

		}
		int addr_size = sizeof(serverAddr);
        
		int f_recv_size = recvfrom(sockfd, &frame_recv, sizeof(frame_recv), 0 ,(struct sockaddr*)&serverAddr, &addr_size);
        

        
		if( f_recv_size > 0 && frame_recv.sq_no == 0 && frame_recv.ack == frame_id+1){
			//printf("[+]Ack Received\n");
        	printf("[+]Ack %d Received\n", frame_recv.sequence);

			ack_recv = 1;
		}else{
			printf("[-]Ack Not Received\n");
			ack_recv = 0;
		}	
  			
		frame_id++;
         


        }

        


    }

	
	close(sockfd);
	return 0;
}
