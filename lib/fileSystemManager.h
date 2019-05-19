
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "string.h"

#include "esp_system.h"
#include "esp_log.h"

#include "nvs_flash.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "dinamicVector.h"
#define LIST 1
#define FOLDER 2
#define CAT 3
#define CREATE 4
#define EDIT 5
#define DELETE 6

void fileSystemManager(message_t * message, esp_vfs_fat_mount_config_t mount_config);