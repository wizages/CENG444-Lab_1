#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#define MYPORT 3490 // the port users will be connecting to, below 1024 are reserved
#define BACKLOG 10 // how many pending connections queue will hold
#define MAXDATASIZE 256 // max number of bytes we can get at once
int main() {
  int sockfd, new_fd, i; // listen on sockfd, new connection on new_fd, counter
  struct sockaddr_in my_addr; // my address information (server)
  struct sockaddr_in their_addr; // client's address information
  char buf[MAXDATASIZE];
  int sin_size;
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { 
    perror("socket");
    exit(1);
  }
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(MYPORT); //convert host byte order to network byte order
  my_addr.sin_addr.s_addr = htonl(INADDR_ANY); // automatically fill with my IP
  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) { 
    perror("bind");
    exit(1);
  }
  if (listen(sockfd, BACKLOG) == -1) { 
    perror("listen");
    exit(1);
  }
  while(1) {
    sin_size = sizeof(struct sockaddr_in);
    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
      perror("accept");
      continue; 
    }
    printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
    /* the inet_ntoa() function converts the Internet host address , given in network byte order, to a
    string in IPv4 dotted-decimal notation. */
    if (recv(new_fd, buf, MAXDATASIZE, 0) < 0) { 
      perror("read");
      exit(1);
      /*
      
      */
    }
    printf("Received: %s\n",buf);
    i = 0;
    while(buf[i] != '\0')
    {
      buf[i] = buf[i] + 1;
      i++;
    }

    if(send(new_fd, buf, MAXDATASIZE, 0) < 0)
      {
        perror("send");
        exit(1);
      }
    close(new_fd);
  } 
}