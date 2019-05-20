#ifndef _SERVER_
#define _SERVER_
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "string.h"

#include "esp_system.h"
#include "esp_log.h"

#include "nvs_flash.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"

void fileSystemManager();
#include "fileSystemManager.c"

#endif