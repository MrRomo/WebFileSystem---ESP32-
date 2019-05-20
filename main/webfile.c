
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

#include "lib/AP_Manager.h"
#include "lib/Server.h"
#include "lib/fileSystemManager.c"

void serverTask()
{
    server();
}

void fileSystemTask()
{
    esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 4,
        .format_if_mount_failed = false};
    while (1)
    {
        printf("start partition\n");
        if (esp_vfs_fat_spiflash_mount("/vsd", "storage", &mount_config, &s_wl_handle) == ESP_OK)
        {
            printf("Partition OK\n");
            while (1)
            {
                char req;
                xQueueReceive(fileSystemReq, &req, portMAX_DELAY);    
                printf("Req received %d", req);
                fileSystemManager(req);
            }
            
        }
        else
        {
            while (1)
            {
                printf("Mounting Partition ERROR \n");
                vTaskDelay(1000 / portTICK_RATE_MS);
            }
        }
    }
}

void app_main()
{

    //Inicialización NVS (Non Volatile Storage)
    ESP_ERROR_CHECK(nvs_flash_init());
    fileSystemReq = xQueueCreate(2, sizeof(char));
    fileSystemRes = xQueueCreate(2, sizeof(char)*10);

    AP_init(); //Init AP Manager
    printf("AP Started\n");
    xTaskCreate(fileSystemTask, "fileSystemTask", 4096, NULL, 4, NULL);
    xTaskCreate(serverTask, "serverTask", 4096, NULL, 4, NULL); //Init server Task
    // testFileSystem(mount_config);
}
