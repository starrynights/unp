#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 80
#define SERV_PORT 8000

int main (int argc, char ** argv)
{
	struct sockaddr_in servaddr, cliaddr;
	int listenfd, connfd;
	socklen_t cliaddr_len, servaddr_len;
	char buf[MAXLINE];
	char str[INET_ADDRSTRLEN];
	int i, n;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	
	bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(listenfd, 20);
	printf("accepting connections ...\n");
	while(1)
	{
		cliaddr_len = sizeof(cliaddr);
		servaddr_len = sizeof(servaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
		n = read(connfd, buf,MAXLINE);

		//print server address
		struct sockaddr_in ss;
		if (0 == getsockname(connfd, (struct sockaddr *)&ss, &servaddr_len))
		{
			printf("server family: %d\n", ss.sin_family);
			char s[INET_ADDRSTRLEN];
			printf("server address: %s\n", 
					inet_ntop(AF_INET, &ss.sin_addr, s, sizeof(s)));
			printf("server port: %d\n", ss.sin_port);
		}

		printf("received from %s at PORT %d\n", 
				inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), 
				ntohs(cliaddr.sin_port));
		printf("%s\n", buf);
		for (i = 0; i < n; i ++)
		{
			buf[i] = toupper(buf[i]);
		}
		write(connfd, buf, n);
		close(connfd);
	}
}
