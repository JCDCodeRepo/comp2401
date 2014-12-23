#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_BUF  64
#define MAX_ARGS  8

void initShell(int*);
void parse(char*, char**);

int main()
{
  char cmd[MAX_BUF];
  char **args;
  int  socket;
  int  i;

/* allocate memory for command arguments */
  args = (char **) calloc(MAX_ARGS, sizeof(char*));
  for (i=0; i<MAX_ARGS; ++i)
    args[i] = (char *) calloc(MAX_BUF, sizeof(char));

/* initialize socket and connect to logger */
  initShell(&socket);

/* prompt user for shell command, fork another 
   process to execute */
  while (1) {
    printf("<cuShell> ");
    fgets(cmd, sizeof(cmd), stdin);
    cmd[strlen(cmd)-1] = 0;
    if (strcmp(cmd, "exit") == 0)
      break;
    int pid = fork();
    if (pid != 0) {
      send(socket, cmd, strlen(cmd), 0);
    }
    else {
      parse(cmd, args);
      execvp(args[0], args);
      exit(0);
    }
  }

  if (getpid() != 0)
    send(socket, "exit", strlen("exit"), 0);

/* clean up */
  for (i=0; i<MAX_ARGS; ++i)
    free(args[i]);
  free(args);

  return 0;
}

/*    Purpose:  creates a socket, getting
                it ready to be used to send data
                through
           in:  pointer to the socket to be created
          out:  pointer to the socket created (through output parameter)
*/
void initShell(int *sock)
{
  FILE *configFile;
  char ip[MAX_BUF];
  int  port;

/*  get IP address and port number from config file */
  if (!(configFile=fopen(".config","r"))) {
    printf("cannot read config file...\n");
    exit(1);
  }
  fscanf(configFile, "%s", ip);
  fscanf(configFile, "%d", &port);
  fclose(configFile);

/*  create socket and connect to logger */
  struct sockaddr_in  addr;
  int i;

/* create socket */
  *sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (*sock < 0) {
    printf("eek! couldn't open socket\n");
    exit(-1);
  }

/* setup address */
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons((unsigned short) port);

/* connect to server */
  i = connect(*sock, 
              (struct sockaddr *) &addr,
              sizeof(addr));
  if (i<0) {
    printf("client could not connect!\n");
    exit(-1);
  }

}

/*    Purpose:  parses a line into several arguments 
                (shamelessly "borrowed" off the internet)
           in:  line to be parsed
          out:  array of strings, representing each argument
*/
void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
     *argv = '\0';                 /* mark the end of argument list  */
}

