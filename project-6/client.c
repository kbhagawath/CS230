#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


#define MAXLINE 8192

char* encode_cipher (char buf[], char msg[]){

  char* split = strtok(buf, " ");
  int s;

  split = strtok(NULL, " ");
  split = strtok(NULL, " ");
  s = atoi(split);
  split = strtok(NULL, " ");

  for ( int j = 0; j < strlen(split); j++){
    split[j] = split[j] + s;

    while(split[j] > 'Z'){
      split[j] = split[j] - 'Z' + 'A' - 1;
    }
  }

  int z = 6;
  for (int k = 0; k < strlen(split); k++){
    msg[z] = split[k];
    z++;
  }
  msg[strlen(msg)] = '\n';
  return msg;
}

int open_clientfd(char *hostname, int port) {
  // The client's socket file descriptor.
  int clientfd;

  // The hostent struct is used to get the IP address of the server
  // using DNS.
  //
  // struct hostent {
  //   char *h_name;        // official domain name of host
  //   char **h_aliases;    // null-terminated array of domain names
  //   int  h_addrtype;     // host address type (AF_INET)
  //   int  h_length;       // length of an address, in bytes
  //   char **h_addr_list;  // null-terminated array of in_addr structs
  // };
  struct hostent *hp;

  // serveraddr is used to record the server information (IP address
  // and port number).
  //
  // struct sockaddr_in {
  //   short            sin_family;   // e.g. AF_INET
  //   unsigned short   sin_port;     // e.g. htons(3490)
  //   struct in_addr   sin_addr;     // see struct in_addr, below
  //   char             sin_zero[8];  // zero this if you want to
  // };
  struct sockaddr_in serveraddr;

  printf("Echo Client is creating a socket.\n");

  // First, we create the socket file descriptor with the given
  // protocol and protocol family.
  if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

  // Query DNS for the host (server) information.
  if ((hp = gethostbyname(hostname)) == NULL) return -2;

  // The socket API requires that you zero out the bytes!
  bzero((char *)&serveraddr, sizeof(serveraddr));

  // Record the protocol family we are using to connect.
  serveraddr.sin_family = AF_INET;

  // Copy the IP address provided by DNS to our server address
  // structure.
  bcopy((char *)hp->h_addr_list[0], (char *)&serveraddr.sin_addr.s_addr,
        hp->h_length);

  // Convert the port from host byte order to network byte order and
  // store this in the server address structure.
  serveraddr.sin_port = htons(port);

  printf("Echo Client is trying to connect to %s (%s:%d).\n", hostname,
         inet_ntoa(serveraddr.sin_addr), port);

  // Establish a connection with the server.
  if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    return -1;

  printf("Echo Client connected.\n");

  // Return the connected file descriptor.
  return clientfd;
}

int main( int argc, char **argv){

  if (argc != 4){
      fprintf(stderr, "Usage: %s <NETID>@umass.edu <port> <ipAddress>\n", argv[0]);
      exit(0);
  }

char *message = (char *)malloc(256);

char *email = "student@cs.umass.edu";

sprintf(message, "Hello %s\n", email);

  char* NETID = argv[1];
  int port = atoi(argv[2]);
  char* ipAddress = argv[3];
  char buf[MAXLINE];

  int client; 
  client = open_clientfd(ipAddress, port);

  char msg[MAXLINE] = "cs230 HELLO ";
  strcat(msg, argv[1]);
  strcat(msg, "\n");

  send(client, msg, strlen(msg), 0);

  while(1){
    recv(client, buf, MAXLINE, 0);
    buf[strcspn(buf, "\n")] = '\0';
    printf("Message received: %s\n", buf);

    if(strstr(buf, "bye")){			
      break;
    }

    char rec[MAXLINE] = "cs230 ";
    char *encrypt = encode_cipher(buf, rec); 
    printf("Encrypted message to send: %s\n", encrypt);
    send(client, encrypt, strlen(encrypt), 0);

  }

  close(client);
  exit(0);
}

