
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "nvs_flash.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"

#include "lib/AP_Manager.h"

// #include "fileSystemManager.h"
// static wl_handle_t s_wl_handle = WL_INVALID_HANDLE;

// SemaphoreHandle_t 

//     void
//     serverTask()
// {
//     while (1)
//     {
//         server();
//     }
// }
// void fileSystemTask()
// {

//     esp_vfs_fat_mount_config_t mount_config = {
//         .max_files = 4,
//         .format_if_mount_failed = false};

//     printf("Creando SD Virtual\r\n");
//     printf("virtual file system [OK]\r\n");

//     if (esp_vfs_fat_spiflash_mount("/vsd", "storage", &mount_config, &s_wl_handle) == ESP_OK)
//     {
//     }
//     else
//     {
//         printf("Error\r\n");
//     }
//     ESP_ERROR_CHECK(nvs_flash_init());
// }
void APTask()
{
    AP_init();
    printf("AP Started\n");
}

void app_main()
{

    xTaskCreate(serverTask, "serverTask", 4096, NULL, 4, NULL);
    xTaskCreate(fileSystemTask, "fileSystemTask", 4096, NULL, 4, NULL);
    xTaskCreate(fileSystemTask, "fileSystemTask", 4096, NULL, 4, NULL);
    // testFileSystem(mount_config);
}
