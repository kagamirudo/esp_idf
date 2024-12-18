#ifndef SERVICE_H
#define SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "esp_http_server.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rcl/error_handling.h>
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/string.h>
#include <uros_network_interfaces.h>

#include "light_control.h"

#ifdef CONFIG_MICRO_ROS_ESP_XRCE_DDS_MIDDLEWARE
#include <rmw_microros/rmw_microros.h>
#endif

#define ERROR
#ifdef ERROR
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
#endif

// Comment either one to build
#define ROOT // Act as light time overall
// #define CHILD // Follow root's light and inverse if needed

#ifdef ROOT
const char *TAG = "Traffic Root";
#else
const char *TAG = "Traffic Node";
#endif

#define ARRAY_LEN 100
bool run = false;
TaskHandle_t led_task_handle = NULL;

rcl_publisher_t publisher;
std_msgs__msg__String send_msg;

#ifdef ROOT
rcl_subscription_t subscriber;
std_msgs__msg__String recv_msg;
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
#endif

void init_msg_string(std_msgs__msg__String *msg)
{
    msg->data.data = (char *)malloc(ARRAY_LEN * sizeof(char));
    msg->data.size = 0;
    msg->data.capacity = ARRAY_LEN;
}

void echo_light_status()
{
    if (!run)
        snprintf(send_msg.data.data, ARRAY_LEN, "Light Status: OFF");
    else
        snprintf(send_msg.data.data, ARRAY_LEN, "Light Status: ON");
    send_msg.data.size = strlen(send_msg.data.data);
    RCSOFTCHECK(rcl_publish(&publisher, &send_msg, NULL));
    // printf("Sent: %s", send_msg.data.data);
}

void led_task(void *pvParameters)
{
    while (1)
    {
        if (run)
        {
            run_traffic_light_sequence(traffic_lights, traffic_light_timeout, light_count);
        }
        else
        {
            delay_seconds(1);
        }
        echo_light_status();
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

    // Create publisher.
    ESP_LOGI(TAG, "Creating publisher");
    RCCHECK(rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
        "led_pub"));

    // Create subscriber
    ESP_LOGI(TAG, "Creating subscriber");
    RCCHECK(rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
        "led_sub"));

    // Create executor
    ESP_LOGI(TAG, "Creating executor");
    rclc_executor_t executor = rclc_executor_get_zero_initialized_executor();
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));

    // Initialize the message - really important
    init_msg_string(&send_msg);
    init_msg_string(&recv_msg);

    RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &recv_msg,
                                           &subscription_callback, ON_NEW_DATA));

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
    RCCHECK(rcl_publisher_fini(&publisher, &node));
    RCCHECK(rcl_node_fini(&node));

    vTaskDelete(NULL);
}

#endif