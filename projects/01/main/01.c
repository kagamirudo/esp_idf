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

#include "esp_spiffs.h"

#include "my_data.h"

#define GREEN_LED 18
#define YELLOW_LED 19
#define RED_LED 21

static const char *TAG = "Traffic Light Control";

static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START:
        printf("WiFi connecting ... \n");
        break;
    case WIFI_EVENT_STA_CONNECTED:
        printf("WiFi connected ... \n");
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        printf("WiFi lost connection ... \n");
        break;
    case IP_EVENT_STA_GOT_IP:
        printf("WiFi got IP ... \n\n");
        break;
    default:
        break;
    }
}

void wifi_connection()
{
    // 1 - Wi-Fi/LwIP Init Phase
    esp_netif_init();                    // TCP/IP initiation 					s1.1
    esp_event_loop_create_default();     // event loop 			                s1.2
    esp_netif_create_default_wifi_sta(); // WiFi station 	                    s1.3
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_initiation); // 					                    s1.4
    // 2 - Wi-Fi Configuration Phase
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = SSID,
            .password = PASS}};
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
    // 3 - Wi-Fi Start Phase
    esp_wifi_start();
    // 4- Wi-Fi Connect Phase
    esp_wifi_connect();
}

esp_err_t get_handler(httpd_req_t *req)
{
    const char resp[] = "<!DOCTYPE HTML><html><head>\
                            <title>ESP Input Form</title>\
                            <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
                            </head><body>\
                            <form action=\"/get\">\
                                str: <input type=\"text\" name=\"str\">\
                                <input type=\"submit\" value=\"Submit\">\
                            </form><br>\
                            <form action=\"/get\">\
                                int: <input type=\"text\" name=\"int\">\
                                <input type=\"submit\" value=\"Submit\">\
                            </form><br>\
                            </body></html>";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t get_handler_str(httpd_req_t *req)
{
    // Read the URI line and get the host
    char *buf;
    size_t buf_len;
    buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
    if (buf_len > 1)
    {
        buf = malloc(buf_len);
        if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK)
        {
            ESP_LOGI(TAG, "Host: %s", buf);
        }
        free(buf);
    }

    // Read the URI line and get the parameters
    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len > 1)
    {
        buf = malloc(buf_len);
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK)
        {
            ESP_LOGI(TAG, "Found URL query: %s", buf);
            char param[32];
            if (httpd_query_key_value(buf, "str", param, sizeof(param)) == ESP_OK)
            {
                ESP_LOGI(TAG, "The string value = %s", param);
            }
            if (httpd_query_key_value(buf, "int", param, sizeof(param)) == ESP_OK)
            {
                ESP_LOGI(TAG, "The int value = %s", param);
            }
        }
        free(buf);
    }

    // The response
    const char resp[] = "The data was sent ...";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_uri_t uri_get = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = get_handler,
    .user_ctx = NULL};

httpd_uri_t uri_get_input = {
    .uri = "/get",
    .method = HTTP_GET,
    .handler = get_handler_str,
    .user_ctx = NULL};

httpd_handle_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;
    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &uri_get_input);
    }
    return server;
}

void stop_webserver(httpd_handle_t server)
{
    if (server)
    {
        httpd_stop(server);
    }
}

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

    // nvs_flash_init();
    // wifi_connection();
    // start_webserver();

    esp_vfs_spiffs_conf_t config = {
        .base_path = "/storage",
        .partition_label = NULL, // Just one partition
        .max_files = 5,
        .format_if_mount_failed = true};

    esp_err_t result = esp_vfs_spiffs_register(&config);
    if (result != ESP_OK)
        ESP_LOGE(TAG, "Failed to init SPIFFS (%s)", esp_err_to_name(result));
    size_t total = 0, used = 0;
    result = esp_spiffs_info(config.partition_label, &total, &used);
    if (result != ESP_OK)
        ESP_LOGE(TAG, "Failed to get partition info (%s)", esp_err_to_name(result));
    else
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);

    FILE *p = fopen("/storage/index.html", "r+");

    while (1)
    {
        traffic_light_routine(traffic_lights, traffic_light_timeout);
    }
}
