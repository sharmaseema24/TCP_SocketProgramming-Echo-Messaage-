#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>

#define ERROR -1
#define MAX_DATA 1024


int main(int argc, char **argv)
{
	int sock = 0;
	struct sockaddr_in remote_server;
	unsigned int sockaddr_len = sizeof(struct sockaddr_in);
	char input[MAX_DATA];
        char output[MAX_DATA];
	int data_len;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
	{
		perror("Client Socket: ");
		exit(-1);
	}
	remote_server.sin_family = AF_INET;
	remote_server.sin_port = htons(atoi(argv[2])); //port no received as command line argument
	remote_server.sin_addr.s_addr = inet_addr(argv[1]); //ip address received as command line argument
	bzero((void *)&remote_server.sin_zero, 8); //only structure padding
	
	//Connect to Remote Server	
	if(connect(sock, (struct sockaddr *) &remote_server, sockaddr_len) == ERROR){
		perror("Socket Connect  ");
		exit(-1);
	}
	
	while(1){
		fgets(input, MAX_DATA, stdin); 	//receive data from user
		send(sock, input, strlen(input), 0);

		data_len = recv(sock, output, MAX_DATA, 0);
		output[data_len] = '\0'; //Null terminated
		printf("Rcvd: %s \n", output);
		
	}
	close(sock);
	return 0;
}
