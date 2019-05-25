#ifndef _WEB_FILE_
#define _WEB_FILE_

#include "freertos/FreeRTOS.h"
#include "string.h"

#include "freertos/task.h"
#include "freertos/semphr.h"
#include <freertos/queue.h>

#include "nvs_flash.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "tcpip_adapter.h"
#include "esp_event.h"

static wl_handle_t s_wl_handle = WL_INVALID_HANDLE;

xSemaphoreHandle client_connected;

xQueueHandle fileSystemReq;
xQueueHandle fileSystemRes;

#define LIST 1
#define FOLDER 2
#define CAT 3
#define CREATE 4
#define EDIT 5
#define DELETE 6
#define CFOLDER 7

typedef struct message
{
    char req;
    char *first_arg;
    char *res;
    char file[20];
    char folder[20];
    char text[50];
} message_t;

#endif