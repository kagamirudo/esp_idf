#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BLUE_LED 2
#define GREEN_LED 18
#define YELLOW_LED 19
#define RED_LED 21

extern const char *TAG;

const int traffic_lights[] = {GREEN_LED, YELLOW_LED, RED_LED, BLUE_LED};
float traffic_light_timeout[4] = {1, 1, 1, 1};
const size_t light_count = sizeof(traffic_lights) / sizeof(traffic_lights[0]);
extern bool run;

void led_control(int led, bool state)
{
    gpio_set_level(led, state ? 1 : 0);
}

void delay_seconds(float seconds)
{
    vTaskDelay((seconds * 1000) / portTICK_PERIOD_MS);
}

void initialize_traffic_lights(const int *traffic_lights, size_t count)
{
    ESP_LOGI(TAG, "Initializing Traffic Light Control");
    for (size_t i = 0; i < count; i++)
    {
        gpio_reset_pin(traffic_lights[i]);
        gpio_set_direction(traffic_lights[i], GPIO_MODE_OUTPUT);
    }
}

void run_traffic_light_sequence(const int *traffic_lights, const float *timeouts, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (!run)
            break;
        led_control(traffic_lights[i], true);
        delay_seconds(timeouts[i]);
        led_control(traffic_lights[i], false);
    }
}
