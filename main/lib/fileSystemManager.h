#ifndef _FS_MANAGER_
#define _FS_MANAGER_
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "string.h"

#include "esp_system.h"
#include "esp_log.h"

#include "nvs_flash.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "fileSystemManager.c"

void fileSystemManager(char req);


#endif