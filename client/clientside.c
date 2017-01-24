#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 3490 // the port client will be connecting to
#define MAXDATASIZE 256 // max number of bytes we can get at once

int main(int argc, char *argv[]){
  int sockfd, numbytes;
  char buf[MAXDATASIZE];
  struct hostent *he;
  struct sockaddr_in their_addr; // server's address information
  if (argc != 3) {
    fprintf(stderr,"usage: main server_hostname message \n"); exit(1);
  }
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { 
    perror("socket");
    exit(1);
  }
  if ((he=gethostbyname(argv[1])) == NULL) { // get the host info including IP address 
    perror("gethostbyname");
    exit(1);
  }

  their_addr.sin_family = AF_INET;
  their_addr.sin_port = htons(PORT); //convert host byte order to network byte order 
  memcpy(&their_addr.sin_addr, he->h_addr, he->h_length);

  if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
    perror("connect");
    exit(1); 
  }
  if(send(sockfd, argv[2], MAXDATASIZE, 0) < 0)
  {
    perror("send");
    exit(1);
    /*
    */
  }


  if ((numbytes=recv(sockfd, buf, MAXDATASIZE,0)) < 0) { 
      perror("read");
      exit(1);
    }
  printf("Received: %s\n",buf);
  close(sockfd);
}