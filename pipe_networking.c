#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  char * buf = malloc(1024 * sizeof(char));
  
  //create wkp and wait for connection
  mkfifo("waluigi", 0644);
  printf("pipe created\n");
  int from_client = open("waluigi", O_RDONLY);
  printf("pipe opened: %d\n", from_client);
  
  //client creates "private" fifo
  //client sends message to server
  //read(from_client, buf, 1024 * sizeof(char));
  //printf("connection :) we got this: %s\n", buf);

  //server sends response to client
  //close(*to_client);

  read(from_client, buf, 32 * sizeof(char));
  printf("path name: %s\n", buf);  
  int tc = open(buf, O_WRONLY);
  *to_client = tc;
  char * message = "received";
  write(tc, message, 16 * sizeof(char));

  //client sends response to server
  read(from_client, buf, 1024 * sizeof(char));
  printf("second message received: %s\n", buf);

  free(buf);
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char * buf = malloc(1024 * sizeof(char));
  
  //make connection to server
  int ts = open("waluigi", O_WRONLY);
  *to_server = ts;
  //char * message = "hello i'd like to connect\n";
  //write(ts, message, 32 * sizeof(char));
  char * path = "waaah";
  write(ts, path, 32 * sizeof(char));
  //close(*to_server);
  
  //client creates "private" fifo
  mkfifo(path, 0644);
  printf("response pipe created\n");
  
  //client sends message to server
  
  
  printf("path written\n");
  
  //server sends response to client
  int from_server = open("waaah", O_RDONLY);//broken
  printf("response pipe opened\n");
  read(from_server, buf, 1024 * sizeof(char));
  printf("server's message received: %s\n", buf);
  
  //client sends response to server
  char *message = "things are looking groovy";
  
  free(buf);

  return from_server;
}
