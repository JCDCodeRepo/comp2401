#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUF  64

// Allowed global variables 
FILE *logFile;                      //For the output file
int listenerSocket, clientSocket;   //For the sockets (so we can close both of them via the cleanup function)


void handleSigInt(int);
void clean_up();


int main()
{
  // The Signal Handler for SIGINT
  signal(SIGINT, handleSigInt);

  FILE *configFile;
  char logName[MAX_BUF];
  char ip[MAX_BUF];
  int  port;
  char str[MAX_BUF];

/* get IP address and port number from config file */
  if (!(configFile=fopen(".config","r"))) {
    printf("cannot read config file...\n");
    exit(1);
  }
  fscanf(configFile, "%s", ip);
  fscanf(configFile, "%d", &port);
  fclose(configFile);

/* create name of log file;  format is
    username followed by timestamp
    usernameYYYYMMDDHHMM.log */
  strcpy(logName, getenv("USER"));
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(str, "%4d%02d%02d%02d%02d",
          tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
          tm.tm_hour, tm.tm_min);
  strcat(logName, str);
  strcat(logName, ".log");

/* open log file for writing */
  if (!(logFile=fopen(logName,"w"))) {
    printf("cannot write to file...\n");
    exit(1);
  }


/* set up connection, receive commands typed
   into cuShell process, and log them to the
   logFile */

  int  clientSocket;
  struct sockaddr_in  myAddr, clientAddr;
  int i, addrSize, bytesRcv;

  char buffer[MAX_BUF];

/* create socket */

  listenerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (listenerSocket < 0) {
    printf("eek! couldn't open socket\n");
    exit(-1);
  }

/* setup the server address */
  memset(&myAddr, 0, sizeof(myAddr));
  myAddr.sin_family = AF_INET;
  myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myAddr.sin_port = htons((unsigned short) port);

  // Fix to the socket reuse problem mentioned in the course forum
  int optval = 1;
  setsockopt(listenerSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

/* bind the listener socket */
  i = bind(listenerSocket, 
           (struct sockaddr *) &myAddr,
           sizeof(myAddr));
  if (i < 0) {
    printf("eek! couldn't bind socket\n");
    exit(-1);
  }


/* listen */
  i = listen(listenerSocket, 5);
  if (i < 0) {
    printf("eek! couldn't listen\n");
    exit(-1);
  }

/* First while loop to wait for connection request */
  addrSize = sizeof(clientAddr);

  while (1) {
    clientSocket = accept(listenerSocket,
                          (struct sockaddr *) &clientAddr,
                          &addrSize);
    if (clientSocket < 0) {
      printf("eek! couldn't accept the connection\n");
      exit(-1);
    }

  /* This nested while loop writes every argument received until "exit" is received */
    while (1) {
      bytesRcv = recv(clientSocket, buffer, sizeof(buffer), 0);
      buffer[bytesRcv] = 0;
      fprintf(logFile,"%s\n", buffer);
      if(strcmp(buffer,"exit") == 0)
        break;
    } 
    if(strcmp(buffer,"exit") == 0)
        break;
  }
  raise(SIGINT);
  return 0;
}

/* the signal handler for SIGINT
  -invokes the cleanup function */
void handleSigInt(int i)
{
  clean_up();
}

/* the cleanup function
  - closes both the listener and client socket
  - closes output file
  - kill self process
*/
void clean_up(){
  close(clientSocket);
  fclose(logFile);
  close(listenerSocket);
  raise(SIGKILL);
}