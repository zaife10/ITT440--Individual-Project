//NTP Server
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/if.h>
#include <time.h>
#include <stdlib.h>
#define MAX 1000

void func(int sockfd)
{
	char buff[MAX];
	int i;
	//Get current time
	time_t current_time;
	char* c_time_string;
	
	for(;;)
	{
		bzero(buff, MAX);
		time_t now = time(&now);
		int i;
		struct ifreq ifr;
		char array[] = "enp0s8";
		
		//Print current time
		if(now == -1)
		{
			puts("The time() function failed");
		}
		
		struct tm *ptm = gmtime(&now);
		
		if (ptm = NULL)
		{
			puts("The gmtime() function failed");
		}
		
		bzero(buff, sizeof(buff));
		printf("\nCurrent time            : %s", asctime(ptm));
		read(sockfd, buff, sizeof(buff));
		printf("\nClient Name             : %s\n", getlogin());
		printf("Message from client     : %s", buff);
		printf("\nEnter message to client : ");
		i = 0;
		bzero(buff, MAX);
		while ((buff[i++] = getchar()) != '\n');
		if (strncmp("exit", buff, 4) == 0)
		{
			printf("\n[+]Server Exit\n\n");
			break;
		}
		write(sockfd, buff, sizeof(buff));
	}
	i = 0;
}

int main()
{
	time_t now = time(&now);
	int sockfd, connfd, len;
	struct ifreq ifr;
	struct sockaddr_in server, client;
	char array[] = "enp0s8";
	
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd == -1){
		puts("[+]Socket creation failed\n");
		exit(0);
	}
	else{
		printf("\n[+]Socket successfully created\n");
		bzero(&server, sizeof(server));
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(123);
	
	if ((bind(sockfd, (struct sockaddr*)&server, sizeof(server))) !=0){
		puts("[+]Socket bind failed\n");
		exit(0);
	}
	else
		printf("[+]Socket successfully binded\n");
	
	if((listen(sockfd, 5)) !=0){
		puts("[+]Listen failed...\n");
		exit(0);
	}
	else{
		printf("[+]NTP Server listening\n");
		len = sizeof(client);
	}
	
	connfd = accept(sockfd, (struct sockaddr*)&client, &len);
	if (connfd < 0){
		puts("[+]NTP Server accept failed\n");
		exit(0);
	}
	else{
		printf("[+]NTP Server accept the client\n");
		printf("\n[+]This is NTP server\n");
		printf("[+]Waiting message from client\n");
	}
	
	func(connfd);
	close(sockfd);
}
