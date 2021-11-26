#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFSIZE 1024

void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char **argv) {
    int sockfd, portno, n;
    int serverlen;
    struct sockaddr_in servaddr;
    struct hostent *server;
    char *hostname = "255.255.255.255";
    char buf[BUFSIZE];
    char *key;
    char *val;
    
    /* check command line arguments */
    if (argc != 4) {
       fprintf(stderr,"usage: %s <port> <key> <value>\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[1]);
    key = argv[2];
    val = argv[3];



/* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    int broadcastEnable=1;
    int ret=setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,
                       &broadcastEnable, sizeof(broadcastEnable));

    /* gethostbyname: get the server's DNS entry */
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(portno);
    servaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    
    sprintf(buf,"%s=%s\n",key,val);

    /* send the message to the server */
    serverlen = sizeof(servaddr);
    n = sendto(sockfd, buf, strlen(buf), 0,
               (struct sockaddr *)&servaddr, serverlen);
    if (n < 0) 
      error("ERROR in sendto");
    

}
