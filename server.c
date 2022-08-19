#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in server, client;
	int socketfd, c, len, new_socket, n;
	
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd == -1)
	{
		puts("ERR: Socket Creation Failed");
		return -1;
	}
	
	puts("SUCC: Socket Creation Success");
	
	int PORT = atoi(argv[1]);
	
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

