#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define SERVER_PORT 8000
#define MAXLINE 4096
int main(int argc, char *argv[])
{
    struct sockaddr_in serveraddr;
    int confd, len;
    char ipstr[] = "127.0.0.1";
    char buf[MAXLINE];
    confd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, ipstr, &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port  = htons(SERVER_PORT);

    connect(confd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    while(1) {
	    char buf[2048] = {0}; 
	    printf("Please enter the message: ");
	    scanf("%s", buf);
	    write(confd, buf, strlen(buf));
    }

    close(confd);
    return 0;
}
