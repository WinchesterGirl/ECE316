#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SERVER_PORT 4610
#define RECEIVER_PORT 4613

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

int main(int argc, char** argv){

	

	//int port = SERVER_PORT;
	int sockfd,sockfd2;
	struct sockaddr_in serverAddr, newAddr, receiverAddr, newAddr2;
	char buffer[1024];
	socklen_t Server_addr_size,Receiver_addr_size;

	int frame_id=0;
	Frame frame_recv;
	Frame frame_send;	

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    sockfd2 = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	Server_addr_size = sizeof(newAddr);

    memset(&receiverAddr, '\0', sizeof(receiverAddr));
	receiverAddr.sin_family = AF_INET;
	receiverAddr.sin_port = htons(RECEIVER_PORT);
	receiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd2, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr));
	Receiver_addr_size = sizeof(newAddr2);

    char state[]="FRAME";
	while(1){
        int f_recvS_size,f_recvC_size;
        f_recvS_size = recvfrom(sockfd, &frame_recv, sizeof(Frame), 0, (struct sockaddr*)&newAddr, &Server_addr_size);
        
        

		if (f_recvS_size > 0 && frame_recv.frame_kind == 1 && frame_recv.sq_no == frame_id){
			printf("[+]Frame %d Received: %s\n", frame_recv.sequence,frame_recv.packet.data);
			

            frame_send.sq_no = frame_id;
			frame_send.frame_kind = 1;
			frame_send.ack = 0;	
            frame_send.sequence=frame_recv.sequence;	
	
			
			strcpy(frame_send.packet.data, frame_recv.packet.data);
			sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&receiverAddr, sizeof(receiverAddr));
			//printf("[+]Frame Send\n");
            printf("[+]Frame %d Send: %s\n", frame_recv.sequence,frame_recv.packet.data);

            
		}

        
        int Receiver_addr_size = sizeof(receiverAddr);
        f_recvC_size = recvfrom(sockfd, &frame_recv, sizeof(frame_recv), 0, (struct sockaddr*)&newAddr2, &Receiver_addr_size);
        

        if( f_recvC_size > 0 && frame_recv.sq_no == 0 && frame_recv.ack == frame_id+1){
			//printf("[+]Ack Received\n");
			printf("[+]Ack %d Received\n", frame_recv.sequence);
            frame_send.sq_no = frame_recv.sq_no;
			frame_send.frame_kind = frame_recv.frame_kind;
			frame_send.ack = frame_recv.ack;
            frame_send.sequence=frame_recv.sequence;
            
			sendto(sockfd, &frame_send, sizeof(frame_send), 0, (struct sockaddr*)&newAddr, sizeof(newAddr));
			//printf("[+]Ack Send\n");
            printf("[+]Ack %d Send\n", frame_recv.sequence);

		}

        
		frame_id++;	
	}
	
	close(sockfd);
	return 0;
}
