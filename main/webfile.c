#include "lib/dinamicVector.h"
#include "webfile.h"
#include "lib/AP_Manager.h"
#include "lib/Server.h"
#include "lib/fileSystemManager.h"

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
                message_t *fileReq = malloc(sizeof(message_t));
                xQueueReceive(fileSystemReq, fileReq, portMAX_DELAY);
                fileSystemManager(fileReq);
            }
        }
        else
        {
            while (1)
            {
                printf("Mounting Partition ERROR \n");
                printf("Restarting on \n");
                for (size_t i = 0; i < 3; i++)
                {
                    vTaskDelay(1000 / portTICK_RATE_MS);
                    printf("%d... ", i);
                }
                esp_restart();
            }
        }
    }
}

void app_main()
{

    //Inicialización NVS (Non Volatile Storage)

    ESP_ERROR_CHECK(nvs_flash_init());
    fileSystemReq = xQueueCreate(2, sizeof(message_t));
    fileSystemRes = xQueueCreate(2, sizeof(char) * 100);

    AP_init(); //Init AP Manager
    printf("AP Started\n");
    xTaskCreate(fileSystemTask, "fileSystemTask", 4096, NULL, 4, NULL);
    xTaskCreate(serverTask, "serverTask", 4096, NULL, 4, NULL); //Init server Task
    // testFileSystem(mount_config);
}
