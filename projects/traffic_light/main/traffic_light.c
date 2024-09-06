#include <stdio.h>
#include <inttypes.h>
#include <sys/param.h>

#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_server.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_err.h"
#include "esp_spiffs.h"
#include "light_control.h"

extern httpd_handle_t start_server(void);
extern esp_err_t esp32_wifi_connect(void);
bool run = false;

static void init_system(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp32_wifi_connect());
}

void app_main(void)
{
    // Commented SPIFFS initialization code
    // size_t total = 0, used = 0;
    // esp_vfs_spiffs_conf_t config = {
    //     .base_path = "/storage",
    //     .partition_label = NULL, // Just one partition
    //     .max_files = 5,
    //     .format_if_mount_failed = true};
    // esp_err_t result = esp_vfs_spiffs_register(&config);
    // if (result != ESP_OK)
    //     ESP_LOGE(TAG, "Failed to init SPIFFS (%s)", esp_err_to_name(result));
    // result = esp_spiffs_info(config.partition_label, &total, &used);
    // if (result != ESP_OK)
    //     ESP_LOGE(TAG, "Failed to get partition info (%s)", esp_err_to_name(result));
    // else
    //     ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    // FILE *p = fopen("/storage/index.html", "r+");
    // fclose(p);

    init_system();
    initialize_traffic_lights(traffic_lights, light_count);
    start_server();

    while (1)
    {
        if (run)
        {
            run_traffic_light_sequence(traffic_lights, traffic_light_timeout, light_count);
        }
        else
        {
            delay_seconds(10);
        }
    }
}
