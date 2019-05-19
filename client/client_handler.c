#include <stdio.h>      /*for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /*for atoi() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /*for close() */
#include <signal.h>
#include <fcntl.h>
#include "DieWithError.c"
// #include "dinamicVector.c"
#define RCVBUFSIZE 32 /* Size of receive buffer */

#define LIST 1
#define FOLDER 2
#define CAT 3
#define CREATE 4
#define EDIT 5
#define DELETE 6

void DieWithError(char *errorMessage); /* Error handling function */
void handler_signal(int sig);
typedef struct
{
    int req;
    char res[100];
    char filename[100];
    char folder[100];
    char text[100];

} message_t;

int sock; /*Socket descriptor */
char prevMsg[50];
void socketCreator(int port, int client)
{
    struct sockaddr_in echoServAddr; /* Echo server address */
    int bytesRcvd, totalBytesRcvd;   /* /*Bytes read in single recv()and total bytes read */
    struct sockaddr_in server;
    message_t message;
    strcpy(message.text,"test file content");
    strcpy(message.filename,"test.txt");
    strcpy(message.folder, "/vsd");
    
    
    message.req = LIST;

    // message->request = vector_new(5);
    // message->response = vector_new(5);
    // char res[50] = {0};
    // vector_insert(message->request, 0, (void *)LIST); //TYPE OF REQUEST
    // vector_insert(message->request, 1, &res);
    // vector_insert(message->request, 2, "test2.txt");
    // vector_insert(message->request, 3, "/vsd");
    // vector_insert(message->request, 4, "Texto de prueba");

    struct sigaction signal;
    signal.sa_handler = handler_signal;
    sigaction(SIGIO, &signal, 0);

    /* Construct the server address structure */
    sock = socket(PF_INET, SOCK_STREAM, 0); //macro para familia de protocolos de internet SOCK_DGRAM para UDP

    memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
    server.sin_family = AF_INET;                        /* Internet address family */
    server.sin_addr.s_addr = inet_addr("192.168.10.1"); /* Server IP address */
    server.sin_port = htons(port);                      /* Server port */

    /* Establish the connection to the echo server */
    printf("Sending REQ: %d - Filename: %s\r\n", message.req, message.filename);
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
        DieWithError(" connect () failed");
    fcntl(sock, F_SETFL, O_ASYNC);
    fcntl(sock, __F_SETOWN, getpid());
    printf("Connect Successfully¡¡¡\r\nIngrese su mensaje:\r\n");

    while (1)
    {
        fflush(stdin);
        char dato[50];
        fgets(dato, 100, stdin);
        fflush(stdin);
        send(sock, (const void *)&message, sizeof(dato), 0);
    }
}

void handler_signal(int sig)
{
    char buffer[500];
    int recvMsgSize; /* Size of received message */
    memset(buffer, 0, sizeof(buffer));
    if ((recvMsgSize = recv(sock, buffer, sizeof(buffer), 0)) < 0)
        DieWithError("recv() failed");

    char data[500];

    strcpy(data, buffer);
    if (strlen(data) > 0)
    {

        printf("\t-----------\n\t\tmessage: %s\n\t-----------\n", data);
        printf("Ingrese su mensaje:\r\n");
        return;
    }
    memset(buffer, 0, sizeof(buffer));
}
