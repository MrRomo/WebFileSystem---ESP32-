
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "nvs_flash.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
xSemaphoreHandle client_connected;

#include "lib/AP_Manager.h"
#include "lib/Server.h"

// #include "fileSystemManager.h"
// static wl_handle_t s_wl_handle = WL_INVALID_HANDLE;

// SemaphoreHandle_t

void serverTask()
{
    server();
}
void AP_Manager()
{
    AP_init();
    printf("AP Started\n");
}

void app_main()
{

    // xTaskCreate(fileSystemTask, "fileSystemTask", 4096, NULL, 4, NULL);
    AP_Manager(); //Init AP Manager
    xTaskCreate(serverTask, "serverTask", 4096, NULL, 4, NULL); //Init server Task
    // testFileSystem(mount_config);
}
