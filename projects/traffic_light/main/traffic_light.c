#include <stdio.h>
#include <inttypes.h>
#include <sys/param.h>

#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "driver/gpio.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "esp_http_server.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_err.h"
#include "nvs_flash.h"

#include "esp_spiffs.h"

#define GREEN_LED 18
#define YELLOW_LED 19
#define RED_LED 21

static const char *TAG = "Traffic Light Control";

extern httpd_handle_t start_server(void);
extern esp_err_t esp32_wifi_connect(void);

void led_on(int led)
{
    gpio_set_level(led, 1);
}

void led_off(int led)
{
    gpio_set_level(led, 0);
}

void delay(float timeout)
{
    vTaskDelay((timeout * 1000) / portTICK_PERIOD_MS);
}

void set_up_light(int *traffic_lights)
{
    int i;
    ESP_LOGI(TAG, "Traffic Light Control");
    for (i = 0; i < 3; i++)
    {
        gpio_reset_pin(traffic_lights[i]);
        gpio_set_direction(traffic_lights[i], GPIO_MODE_OUTPUT);
    }
}

void traffic_light_routine(int *traffic_lights, float *traffic_light_timeout)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        led_on(traffic_lights[i]);
        delay(traffic_light_timeout[i]);
        led_off(traffic_lights[i]);
    }
}

void app_main(void)
{
    int traffic_lights[] = {GREEN_LED, YELLOW_LED, RED_LED};
    float traffic_light_timeout[] = {20, 2, 20};
    set_up_light(traffic_lights);

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

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(esp32_wifi_connect());

    start_server();

    while (1)
    {
        traffic_light_routine(traffic_lights, traffic_light_timeout);
    }
}