#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include "client_handler.c"

#define RCVBUFSIZE 32 /* Size of receive buffer */

void DieWithError(char *errorMessage); /* Error handling function */
void socketCreator(int port, int client);
void handler_signal(int sig);

int sock;

int main()
{

    while (1)
    {
        socketCreator(80, 0);
    }
}
