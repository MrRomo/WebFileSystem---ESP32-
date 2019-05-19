#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "string.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"

#include "nvs_flash.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "mqtt_client.h"
#include "tcpip_adapter.h"
#include "esp_event.h"
#define WIFI_SSID "linux"
#define WIFI_PASS "s5F1iqZM"

// #include "fileSystemManager.c"
// #include "dinamicVector.h"

typedef struct
{
	int req;
	char res[100];
	char filename[100];
	char folder[100];
	char text[100];

} message_t;

xSemaphoreHandle client_connected;
xSemaphoreHandle mqtt_borker_connect;

int commandLine(char *req, char *res);


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
					//Recibir mensajes
					printf("Buffer\n");
					message_t message;
					message = *(message_t *)buffer;
					printf("Buffer\n");
					printf("REQ: %d \n", message.req);
					printf("Filename: %d \n", (char)message.filename);
					printf("Folder: %s \n", message.folder);
					printf("Text: %s \n", message.text);
					// // if (commandLine(&req, &res))
					// {
					// 	send(sock_client, (const void *)&res, sizeof(res), 0);
					// 	printf("Server*** req %s : res %s\n", req, res);
					// }
				}

				printf("Cliente desconectado\n");
				close(sock_client);
			}
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
	}
}

int commandLine(char *req, char *res)
{
	if (!strstr(req, "ls"))
	{
		strcpy(res, "ls response\n");
		return 1;
	}
	else if (!strstr(req, "ls"))
	{
		strcpy(res, "cd response\n");
		return 1;
	}
	return 0;
}