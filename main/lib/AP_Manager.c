
#include "AP_Manager.h"



static esp_err_t event_handler(void *ctx, system_event_t *event)
{
	printf("Eventos de Wifi %d\r\n", event->event_id);
	switch (event->event_id)
	{

	case SYSTEM_EVENT_AP_START:
		printf("AP inicializado OK\n");
		break;

	case SYSTEM_EVENT_AP_STACONNECTED:
		xSemaphoreGive(client_connected);
		break;

	default:
		break;
	}

	return ESP_OK;
}


// Main application
void AP_init()
{
	//Deshabilitamos log eventos wifi
	esp_log_level_set("wifi", ESP_LOG_NONE);

	//Inicialización NVS (Non Volatile Storage)
	ESP_ERROR_CHECK(nvs_flash_init());

	tcpip_adapter_init();

	ESP_ERROR_CHECK(tcpip_adapter_dhcps_stop(TCPIP_ADAPTER_IF_AP));
	tcpip_adapter_ip_info_t info;
	memset(&info, 0, sizeof(info));
	IP4_ADDR(&info.ip, 192, 168, 10, 1);
	IP4_ADDR(&info.gw, 192, 168, 10, 1);
	IP4_ADDR(&info.netmask, 255, 255, 255, 0);
	ESP_ERROR_CHECK(tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &info));
	ESP_ERROR_CHECK(tcpip_adapter_dhcps_start(TCPIP_ADAPTER_IF_AP));

	ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

	wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));

	wifi_auth_mode_t auth = WIFI_AUTH_OPEN;

	wifi_config_t ap_config = {
		.ap = {
			.ssid = "Wifi_esp32",
			.password = "embebidos",
			.ssid_len = 0,
			.channel = 10,
			.authmode = auth,
			.ssid_hidden = 0,
			.max_connection = 4,
			.beacon_interval = 100,
		},
	};

	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &ap_config));
	ESP_ERROR_CHECK(esp_wifi_start());

	printf("Inicializando AP\r\n");

	client_connected = xSemaphoreCreateBinary();

	//Tarea principal
}
