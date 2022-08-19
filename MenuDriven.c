
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

char IP[100];
int PORT;

int server()
{
	printf("Enter PORT Number: \n");
	scanf("%d", &PORT);
	
	struct sockaddr_in server, client;
	int socketfd, c, len, new_socket, n;
	
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd == -1)
	{
		puts("ERR: Socket Creation Failed");
		return -1;
	}
	
	puts("SUCC: Socket Creation Success");
	
	
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	
	if( bind(socketfd, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		puts("ERR: Bind Failed");
		return -1;
	}
	
	puts("SUCC: Bind Success");
	
	listen(socketfd, 1);
	
	puts("Server is Live Now...");
	
	c = sizeof(struct sockaddr_in);
	len = sizeof(client);
	new_socket = accept(socketfd, (struct sockaddr*)&client, &len);	//(socklen_t *)&c

	if(new_socket < 0)
	{
		puts("ERR: Acceptance Failed");
		return -1;
	}

	puts("New Connection Accepted");

	shutdown(socketfd, SHUT_RD);

	char message[100];
	
	while(1)
	{
		bzero(message, sizeof(message));

		read(new_socket, message, sizeof(message));

		printf("\nClient: %sYou: ", message);

		bzero(message, 100);
		n = 0;
		
		while ((message[n++] = getchar()) != '\n'); 
		write(new_socket, message, sizeof(message));
		
		if(strncmp(message, "bye", 3) == 0)		
		{
			printf("\n\t...EXITING...\n");
			break;
		}
	}
	
	close(socketfd);
	
	return 0;
}

int client()
{
	printf("Enter IP Address: \n");
	scanf("%s", IP);
	printf("Enter PORT Number: \n");
	scanf("%d", &PORT);
	
	struct sockaddr_in server;
	int socketfd, n;
	
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd == -1)
	{
		puts("ERR: Socket Creation Failed");
		return -1;
	}
	
	puts("SUCC: Socket Creation Success");
	
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

int main()
{
	int ch;
	
	
	
	while(1)
	{
		printf("Continue as..?\n");
		printf("\t1. Server\n");
		printf("\t2. Client\n");
		printf("\t3. Exit\n");
		printf("choose (1/2): \n");
		scanf("%d", &ch);
		
		switch(ch)
		{
			case 1: server();
			case 2: client();
			case 3: exit(-1);
			default: printf("wrong input\n");
		}
	}
	
	return 0;
}

