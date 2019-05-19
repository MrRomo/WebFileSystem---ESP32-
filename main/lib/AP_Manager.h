#ifndef _AP_Manager_
#define _AP_Manager_
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
    
    static esp_err_t event_handler(void *ctx, system_event_t *event);

#endif