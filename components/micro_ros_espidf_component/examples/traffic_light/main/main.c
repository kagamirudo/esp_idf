#include <stdio.h>
#include <inttypes.h>
#include <sys/param.h>
#include <unistd.h>

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

#include <uros_network_interfaces.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <std_msgs/msg/int32.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#ifdef CONFIG_MICRO_ROS_ESP_XRCE_DDS_MIDDLEWARE
#include <rmw_microros/rmw_microros.h>
#endif

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
extern httpd_handle_t start_server(void);
extern esp_err_t esp32_wifi_connect(void);
bool run = true;

rcl_subscription_t subscriber;
std_msgs__msg__Int32 msg;

void subscription_callback(const void *msgin)
{
    const std_msgs__msg__Int32 *msg = (const std_msgs__msg__Int32 *)msgin;
    printf("Received: %ld", msg->data);
    run = (msg->data > 0);
    run_traffic_light_sequence(traffic_lights, traffic_light_timeout, light_count);
}

void micro_ros_task(void *arg)
{
    rcl_allocator_t allocator = rcl_get_default_allocator();
    rclc_support_t support;

    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
    
    // Create init_options
    // rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
    // RCCHECK(rcl_init_options_init(&init_options, allocator));

    // RCCHECK(rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator));

    // Create node
    rcl_node_t node = rcl_get_zero_initialized_node();
    RCCHECK(rclc_node_init_default(&node, "traffic_controller", "", &support));

    // Create subscriber
    ESP_LOGI(TAG, "Creating subscriber");
    RCCHECK(rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "led"));

    // Create executor
    ESP_LOGI(TAG, "Creating executor");
    rclc_executor_t executor = rclc_executor_get_zero_initialized_executor();
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
    RCCHECK(rclc_executor_add_subscription(&executor, &subscriber, &msg, &subscription_callback, ON_NEW_DATA));

    initialize_traffic_lights(traffic_lights, light_count);

    while (1)
    {
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
        delay_seconds(1);
    }

    // Clean up
    ESP_LOGI(TAG, "Cleaning up");
    RCCHECK(rcl_subscription_fini(&subscriber, &node));
    RCCHECK(rcl_node_fini(&node));
    // RCCHECK(rclc_support_fini(&support));

    vTaskDelete(NULL);
}

void app_main(void)
{
#if defined(CONFIG_MICRO_ROS_ESP_NETIF_WLAN) || defined(CONFIG_MICRO_ROS_ESP_NETIF_ENET)
    ESP_LOGI(TAG, "Initializing uROS network interface");
    ESP_ERROR_CHECK(uros_network_interface_initialize());
#endif

    ESP_LOGI(TAG, "Creating micro-ROS task");
    // Create micro-ROS task
    xTaskCreate(micro_ros_task,
                "uros_task",
                CONFIG_MICRO_ROS_APP_STACK,
                NULL,
                CONFIG_MICRO_ROS_APP_TASK_PRIO,
                NULL);
}
