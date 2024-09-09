#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/param.h>

#include "esp_log.h"
#include "esp_err.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_spiffs.h"
#include "freertos/task.h"
#include "light_control.h"
#include "esp_http_server.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#include <string.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rcl/error_handling.h>
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/string.h>
#include <uros_network_interfaces.h>

#ifdef CONFIG_MICRO_ROS_ESP_XRCE_DDS_MIDDLEWARE
#include <rmw_microros/rmw_microros.h>
#endif

#define ARRAY_LEN 100

#define RCCHECK(fn)                                                                      \
    {                                                                                    \
        rcl_ret_t temp_rc = fn;                                                          \
        if ((temp_rc != RCL_RET_OK))                                                     \
        {                                                                                \
            printf("Failed status on line %d: %d. Aborting.\n", __LINE__, (int)temp_rc); \
            vTaskDelete(NULL);                                                           \
        }                                                                                \
    }

#define RCSOFTCHECK(fn)                                                                    \
    {                                                                                      \
        rcl_ret_t temp_rc = fn;                                                            \
        if ((temp_rc != RCL_RET_OK))                                                       \
            printf("Failed status on line %d: %d. Continuing.\n", __LINE__, (int)temp_rc); \
    }

const char *TAG = "Traffic Light";
TaskHandle_t led_task_handle = NULL;
bool run = false;

rcl_subscription_t subscriber;
std_msgs__msg__String msg;

void led_task(void *pvParameters)
{
    while (1)
    {
        if (run)
            run_traffic_light_sequence(traffic_lights, traffic_light_timeout, light_count);
        else
            delay_seconds(1);
    }
}

void subscription_callback(const void *msgin)
{
    int i, parsed;
    float timeouts[3] = {0};
    const std_msgs__msg__String *str = (const std_msgs__msg__String *)msgin;

    if (str == NULL)
    {
        ESP_LOGE(TAG, "Received NULL message");
        return;
    }

    if (strcmp(str->data.data, "stop") == 0)
        run = false;
    else
    {
        parsed = sscanf(str->data.data, "%f %f %f", &timeouts[0], &timeouts[1], &timeouts[2]);

        if (parsed == 3)
        {
            ESP_LOGI(TAG, "Received: green=%0.2f(s), yellow=%0.2f(s), red=%0.2f(s)", timeouts[0], timeouts[1], timeouts[2]);
            for (i = 0; i < light_count && i < 3; i++)
                traffic_light_timeout[i] = timeouts[i];
            run = true;
        }
        else
            ESP_LOGE(TAG, "Received: Invalid. Expected 3 floats [Green, Yellow, Red] or 'stop'.");
    }
}

void micro_ros_task(void *arg)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();
    rclc_support_t support;

    // Create init_options
    rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
    RCCHECK(rcl_init_options_init(&init_options, allocator));

#ifdef CONFIG_MICRO_ROS_ESP_XRCE_DDS_MIDDLEWARE
    rmw_init_options_t *rmw_options = rcl_init_options_get_rmw_init_options(&init_options);
    RCCHECK(rmw_uros_options_set_udp_address(CONFIG_MICRO_ROS_AGENT_IP, CONFIG_MICRO_ROS_AGENT_PORT, rmw_options));
#endif
    // Setup support structure.
    RCCHECK(rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator));

    // Create node
    rcl_node_t node = rcl_get_zero_initialized_node();
    RCCHECK(rclc_node_init_default(&node, "traffic_controller", "", &support));

    // Create subscriber
    ESP_LOGI(TAG, "Creating subscriber");
    RCCHECK(rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
        "led"));

    // Create executor
    ESP_LOGI(TAG, "Creating executor");
    rclc_executor_t executor = rclc_executor_get_zero_initialized_executor();
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));

    // Initialize the message - really important
    msg.data.data = (char *)malloc(ARRAY_LEN * sizeof(char));
    msg.data.size = 0;
    msg.data.capacity = ARRAY_LEN;

    RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA));

    initialize_traffic_lights(traffic_lights, light_count);

    // Create LED task
    xTaskCreate(led_task, "led_task", 2048, NULL, 5, &led_task_handle);

    while (1)
    {
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        delay_seconds(1);
    }

    // Clean up
    ESP_LOGI(TAG, "Cleaning up");
    RCCHECK(rcl_subscription_fini(&subscriber, &node));
    RCCHECK(rcl_node_fini(&node));

    vTaskDelete(NULL);
}

void app_main(void)
{
#if defined(CONFIG_MICRO_ROS_ESP_NETIF_WLAN) || defined(CONFIG_MICRO_ROS_ESP_NETIF_ENET)
    ESP_ERROR_CHECK(uros_network_interface_initialize());
#endif

    xTaskCreate(micro_ros_task,
                "uros_task",
                CONFIG_MICRO_ROS_APP_STACK,
                NULL,
                CONFIG_MICRO_ROS_APP_TASK_PRIO,
                NULL);
}
