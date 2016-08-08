#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>

#define ERROR -1
#define MAX_CLIENTS 5
#define MAX_DATA 1024


int main(int argc, char ** argv)
{
	int sock = 0, new = 0;
	struct sockaddr_in server, client;
	unsigned int sockaddr_len = sizeof(struct sockaddr_in);;
	char data[MAX_DATA];
	int data_len;
	int sent = 0; /*No of bytes sent*/

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
	{
		perror("Server Socket: ");
		exit(-1);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY; //server should bind to all available interfaces on local machine
	bzero((void *)&server.sin_zero, 8); //only structure padding
	
	if(bind(sock, (struct sockaddr *) &server, sockaddr_len) == ERROR){
		perror("Socket Bind  ");
		exit(-1);
	}
		
	if(listen(sock, MAX_CLIENTS) == ERROR){
		perror("Socket Listen  ");
		exit(-1);
	}
	
	while(1){
		if((new = accept(sock, (struct sockaddr *) &client, &sockaddr_len)) == ERROR){
			perror("Accept  ");
			exit(-1);
		}
		
		
	printf("New Client connected from port no. %d and IP %s \n", ntohs(client.sin_port), inet_ntoa(client.sin_addr));

		data_len = 1;

		while(data_len){
		  data_len = recv(new, data, MAX_DATA, 0);
		  //echo received data
		  if(data_len){
			sent = send(new, data, data_len, 0);
			data[data_len] = '\0';
			printf("Sent %d bytes data : %s \n", (data_len-1), data);
		  }
		}	
		printf("Client Disconnected!!!");
		close(new);
	}
	
	return 0;
}
