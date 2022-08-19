#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in server;
	int socketfd, n;
	
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd == -1)
	{
		puts("ERR: Socket Creation Failed");
		return -1;
	}
	
	puts("SUCC: Socket Creation Success");
	
	char *IP = argv[1];
	int PORT = atoi(argv[2]);
	
	printf("Your IP: %s\n", IP);
	printf("Your PORT: %d\n", PORT);
	
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	
	if(connect(socketfd, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		puts("ERR: Connection Failed");
		return -1;
	}
	
	puts("SUCC: Connection Success");
	
	char message[100];
	
	while(1)
	{
		bzero(message, sizeof(message));
		
		printf("\nType Your Message: \n");
		n = 0;
		while ((message[n++] = getchar()) != '\n');
		
		write(socketfd, message, sizeof(message));
		printf("\n\nYou: %s\n", message);
		bzero(message, sizeof(message));
		
		read(socketfd, message, sizeof(message));
		printf("\bServer: %s\n", message);
	
		if(strncmp(message, "bye", 3) == 0)		
		{
			printf("\n\t...EXITING...\n");
			break;
		}
	}
	
	puts("\n\t...Thanks For Using...\n");
	
	close(socketfd);
	
	return 0;
}

