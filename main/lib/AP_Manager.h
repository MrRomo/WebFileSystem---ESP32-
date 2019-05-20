#ifndef _AP_Manager_
#define _AP_Manager_
#include "AP_Manager.c"

    #define WIFI_SSID "linux"
    #define WIFI_PASS "s5F1iqZM"
    
    static esp_err_t event_handler(void *ctx, system_event_t *event);
    void AP_init();


#endif