
#include "Server.h"

void commandLine(char *req)
{
	if (!strcmp(req, "ls\n"))
	{
		req = LIST;
		printf("LIST files req \n");
		xQueueSend(fileSystemReq, &req, portMAX_DELAY);
	}
	else if (!strcmp(req, "cat\n"))
	{
		req = CAT;
		printf("cat files req \n");
		xQueueSend(fileSystemReq, &req, portMAX_DELAY);
	}
	else if (!strcmp(req, "touch\n"))
	{
		req = CREATE;
		printf("cat files req \n");
		xQueueSend(fileSystemReq, &req, portMAX_DELAY);
	}
	else if (!strcmp(req, "rm\n"))
	{
		req = DELETE;
		printf("cat files req \n");
		xQueueSend(fileSystemReq, &req, portMAX_DELAY);
	}
}

void server()
{
	int sock, sock_client, c;
	struct sockaddr_in server, client;
	char buffer[100] = {0};

	while (1)
	{
		xSemaphoreTake(client_connected, portMAX_DELAY);
		printf("Cliente Conectado a la red\r\n");
		while (1)
		{
			sock = socket(AF_INET, SOCK_STREAM, 0);

			server.sin_family = AF_INET;
			server.sin_addr.s_addr = INADDR_ANY;
			server.sin_port = htons(80);

			if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
			{
				printf("Error de binding\r\n");
			}

			printf("Enlace Ok\r\n");

			listen(sock, 3);

			while (1)
			{
				printf("Esperando Conexiones\r\n");
				c = sizeof(struct sockaddr_in);
				sock_client = accept(sock, (struct sockaddr *)&client, (socklen_t *)&c);
				if (sock_client < 0)
				{
					printf("conexión rechazada");
					return;
				}

				printf("Cliente Conectado\r\n");
				memset(buffer, 0, sizeof(buffer));
				while (recv(sock_client, buffer, sizeof(buffer), 0))
				{
					printf("Buffer %s\n", buffer);
					commandLine(buffer);
					
				}
				send(sock_client, (const void *)buffer, sizeof(buffer),0);
				printf("Cliente desconectado\n");
				close(sock_client);
			}
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
	}
}
