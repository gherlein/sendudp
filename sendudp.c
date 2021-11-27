// (c) 2022 Greg Herlein, released under the MIT-0 license

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
    char *payload;
    int payloadLen=0;
    
    /* check command line arguments */
    if (argc != 3) {
       fprintf(stderr,"usage: %s <port> <payload>\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[1]);
    payload = argv[2];
    payloadLen = strlen(payload);
    if(payloadLen>BUFSIZE) {
      fprintf(stderr,"payload must be smaller than 1K\n");
      exit(0);
    }
    
    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    /* enable broadcast */
    int broadcastEnable=1;
    int ret=setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,
                       &broadcastEnable, sizeof(broadcastEnable));

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(portno);
    servaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    
    /* send the message to the server */
    serverlen = sizeof(servaddr);
    n = sendto(sockfd, payload, payloadLen, 0,
               (struct sockaddr *)&servaddr, serverlen);
    if (n < 0) {
      error("ERROR sending UDP broadcast data");
    }

}
