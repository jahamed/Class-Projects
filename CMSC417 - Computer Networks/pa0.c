/*
Author: Javed Ahamed
Class: CMSC417 Project 0

Citations: I used two sources for this project:
1. http://www.awakecoding.com/index.php?option=com_content&view=article&id=15:simple-echo-client-and-server&catid=1:home
2. http://www.beej.us/guide/bgnet/output/html/multipage/index.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
 
#define BUFFER_SIZE  100000
 
int n;
char buffer[BUFFER_SIZE];

int status;
struct addrinfo hints;
struct addrinfo *servinfo; //points to getaddrinfo results
struct addrinfo *temp;

int sockfd;

int main(int argc, char* argv[])
{
	if(argc != 3){ //test if parameters are ok
		printf("Usage: ./pa0 <server ip> <server port>\n");
		exit(0);
	}
 
	//clear hints and fill up struct
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	status = getaddrinfo(argv[1], argv[2], &hints, &servinfo);
 
	//attempt connections
	for(temp = servinfo; temp != NULL; temp = temp->ai_next){
		if((sockfd = socket(temp->ai_family, temp->ai_socktype, temp->ai_protocol)) == -1){
			continue;
		}
		if(connect(sockfd, temp->ai_addr, temp->ai_addrlen) == -1){
			close(sockfd);
			continue;
		}
		break;
	}
	
	if(temp == NULL){
		printf("CLIENT: failed to connect\n");
	}
	
	//while(!feof(stdin)){
		fgets(buffer, BUFFER_SIZE, stdin); //get string from stdin
		send(sockfd, buffer, strlen(buffer), 0); //send string to server

		n = recv(sockfd, buffer, BUFFER_SIZE, 0); //receive msg from server
		buffer[n] = '\0';
		printf("%s", buffer);
	//}
	
	close(sockfd); //close connection
 
  return 0;
}
