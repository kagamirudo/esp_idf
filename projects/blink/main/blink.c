#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "driver/gpio.h"

#include "esp_event.h"
#include "esp_netif.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "protocol_common.h"
#include "file_serving_example_common.h"

#define LED_PIN GPIO_NUM_2 // GPIO pin where the LED is connected

static const char *TAG = "led_control";

// Function to initialize the LED
static void init_led()
{
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
}

// Function to blink the LED
static void blink_led(int interval)
{
    while (1)
    {
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(interval / portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(interval / portTICK_PERIOD_MS);
    }
}

// Handler for the LED control POST request
static esp_err_t led_post_handler(httpd_req_t *req)
{
    char buf[100];
    int ret = httpd_req_recv(req, buf, sizeof(buf));
    if (ret <= 0)
    {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT)
        {
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }
    buf[ret] = '\0';

    char *param = strtok(buf, "=");
    if (param && strcmp(param, "interval") == 0)
    {
        char *value = strtok(NULL, "=");
        if (value)
        {
            int interval = atoi(value);
            ESP_LOGI(TAG, "Blink interval set to %d ms", interval);
            blink_led(interval);
            httpd_resp_sendstr(req, "LED blink interval set successfully");
            return ESP_OK;
        }
    }
    httpd_resp_send_500(req);
    return ESP_FAIL;
}

// Register the URI handlers
static esp_err_t start_led_control_server()
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    httpd_uri_t led_uri = {
        .uri = "/led",
        .method = HTTP_POST,
        .handler = led_post_handler,
        .user_ctx = NULL};

    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &led_uri);
    }
    return ESP_OK;
}

void app_main()
{
    init_led();
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(example_connect());
    ESP_ERROR_CHECK(start_led_control_server());
}
