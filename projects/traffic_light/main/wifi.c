#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "esp_log.h"
#include "esp_wifi.h"
#include "freertos/semphr.h"
#include "esp_netif_types.h"
#include "esp_event_base.h"
#include "esp_err.h"
#include "esp_netif.h"
#include "esp_netif_ip_addr.h"
#include "esp_netif.h"

#include "wifi.h"

static const char *TAG = "esp32_wifi_connect";
static esp_netif_t *s_wifi_sta_netif = NULL;
static SemaphoreHandle_t s_semph_get_ip_addrs = NULL;
#if CONFIG_WIFI_CONNECT_IPV6
static SemaphoreHandle_t s_semph_get_ip6_addrs = NULL;
#endif

static int s_retry_num = 0;

static void handler_on_wifi_disconnect(void *arg, esp_event_base_t event_base,
                                       int32_t event_id, void *event_data)
{
    s_retry_num++;
    if (s_retry_num > CONFIG_WIFI_CONN_MAX_RETRY)
    {
        ESP_LOGI(TAG, "WiFi Connect failed %d times, stop reconnect.", s_retry_num);
        /* let wifi_sta_do_connect() return */
        if (s_semph_get_ip_addrs)
        {
            xSemaphoreGive(s_semph_get_ip_addrs);
        }
#if CONFIG_WIFI_CONNECT_IPV6
        if (s_semph_get_ip6_addrs)
        {
            xSemaphoreGive(s_semph_get_ip6_addrs);
        }
#endif
        wifi_sta_do_disconnect();
        return;
    }
    ESP_LOGI(TAG, "Wi-Fi disconnected, trying to reconnect...");
    esp_err_t err = esp_wifi_connect();
    if (err == ESP_ERR_WIFI_NOT_STARTED)
    {
        return;
    }
    ESP_ERROR_CHECK(err);
}

static void wifi_handler_on_wifi_connect(void *esp_netif, esp_event_base_t event_base,
                                         int32_t event_id, void *event_data)
{
#if CONFIG_WIFI_CONNECT_IPV6
    esp_netif_create_ip6_linklocal(esp_netif);
#endif // CONFIG_WIFI_CONNECT_IPV6
}

static void wifi_handler_on_sta_got_ip(void *arg, esp_event_base_t event_base,
                                       int32_t event_id, void *event_data)
{
    s_retry_num = 0;
    ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
    // if (!wifi_is_our_netif(WIFI_NETIF_DESC_STA, event->esp_netif))
    // {
    //     return;
    // }
    ESP_LOGI(TAG, "Got IPv4 event: Interface \"%s\" address: " IPSTR,
             esp_netif_get_desc(event->esp_netif),
             IP2STR(&event->ip_info.ip));
    if (s_semph_get_ip_addrs)
    {
        xSemaphoreGive(s_semph_get_ip_addrs);
    }
    else
    {
        ESP_LOGI(TAG, "- IPv4 address: " IPSTR ",", IP2STR(&event->ip_info.ip));
    }
}

#if CONFIG_WIFI_CONNECT_IPV6
static void wifi_handler_on_sta_got_ipv6(void *arg, esp_event_base_t event_base,
                                         int32_t event_id, void *event_data)
{
    ip_event_got_ip6_t *event = (ip_event_got_ip6_t *)event_data;
    if (!wifi_is_our_netif(WIFI_NETIF_DESC_STA, event->esp_netif))
    {
        return;
    }
    esp_ip6_addr_type_t ipv6_type = esp_netif_ip6_get_addr_type(&event->ip6_info.ip);
    ESP_LOGI(TAG, "Got IPv6 event: Interface \"%s\" address: " IPV6STR ", type: %s", esp_netif_get_desc(event->esp_netif),
             IPV62STR(event->ip6_info.ip), wifi_ipv6_addr_types_to_str[ipv6_type]);

    if (ipv6_type == WIFI_CONNECT_PREFERRED_IPV6_TYPE)
    {
        if (s_semph_get_ip6_addrs)
        {
            xSemaphoreGive(s_semph_get_ip6_addrs);
        }
        else
        {
            ESP_LOGI(TAG, "- IPv6 address: " IPV6STR ", type: %s", IPV62STR(event->ip6_info.ip), wifi_ipv6_addr_types_to_str[ipv6_type]);
        }
    }
}
#endif // CONFIG_WIFI_CONNECT_IPV6

void wifi_start(void)
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_netif_inherent_config_t esp_netif_config = ESP_NETIF_INHERENT_DEFAULT_WIFI_STA();
    // Warning: the interface desc is used in tests to capture actual connection details (IP, gw, mask)
    esp_netif_config.if_desc = NETIF_DESC_STA;
    esp_netif_config.route_prio = 128;
    s_wifi_sta_netif = esp_netif_create_wifi(WIFI_IF_STA, &esp_netif_config);
    esp_wifi_set_default_wifi_sta_handlers();

    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void wifi_stop(void)
{
    esp_err_t err = esp_wifi_stop();
    if (err == ESP_ERR_WIFI_NOT_INIT)
    {
        return;
    }
    ESP_ERROR_CHECK(err);
    ESP_ERROR_CHECK(esp_wifi_deinit());
    ESP_ERROR_CHECK(esp_wifi_clear_default_wifi_driver_and_handlers(s_wifi_sta_netif));
    esp_netif_destroy(s_wifi_sta_netif);
    s_wifi_sta_netif = NULL;
}

esp_err_t wifi_sta_do_connect(wifi_config_t wifi_config, bool wait)
{
    if (wait)
    {
        s_semph_get_ip_addrs = xSemaphoreCreateBinary();
        if (s_semph_get_ip_addrs == NULL)
        {
            return ESP_ERR_NO_MEM;
        }
#if CONFIG_WIFI_CONNECT_IPV6
        s_semph_get_ip6_addrs = xSemaphoreCreateBinary();
        if (s_semph_get_ip6_addrs == NULL)
        {
            vSemaphoreDelete(s_semph_get_ip_addrs);
            return ESP_ERR_NO_MEM;
        }
#endif
    }
    s_retry_num = 0;
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &handler_on_wifi_disconnect, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_handler_on_sta_got_ip, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, &wifi_handler_on_wifi_connect, s_wifi_sta_netif));
#if CONFIG_WIFI_CONNECT_IPV6
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_GOT_IP6, &wifi_handler_on_sta_got_ipv6, NULL));
#endif

    ESP_LOGI(TAG, "Connecting to %s...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    esp_err_t ret = esp_wifi_connect();
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "WiFi connect failed! ret:%x", ret);
        return ret;
    }
    if (wait)
    {
        ESP_LOGI(TAG, "Waiting for IP(s)");
#if CONFIG_WIFI_CONNECT_IPV4
        xSemaphoreTake(s_semph_get_ip_addrs, portMAX_DELAY);
#endif
#if CONFIG_WIFI_CONNECT_IPV6
        xSemaphoreTake(s_semph_get_ip6_addrs, portMAX_DELAY);
#endif
        if (s_retry_num > CONFIG_WIFI_CONN_MAX_RETRY)
        {
            return ESP_FAIL;
        }
    }
    return ESP_OK;
}

esp_err_t wifi_sta_do_disconnect(void)
{
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &handler_on_wifi_disconnect));
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_handler_on_sta_got_ip));
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, &wifi_handler_on_wifi_connect));
#if CONFIG_WIFI_CONNECT_IPV6
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_GOT_IP6, &wifi_handler_on_sta_got_ipv6));
#endif
    if (s_semph_get_ip_addrs)
    {
        vSemaphoreDelete(s_semph_get_ip_addrs);
    }
#if CONFIG_WIFI_CONNECT_IPV6
    if (s_semph_get_ip6_addrs)
    {
        vSemaphoreDelete(s_semph_get_ip6_addrs);
    }
#endif
    return esp_wifi_disconnect();
}

void wifi_shutdown(void)
{
    wifi_sta_do_disconnect();
    wifi_stop();
}

esp_err_t wifi_connect(void)
{
    ESP_LOGI(TAG, "Start wifi_connect.");
    wifi_start();
    wifi_config_t wifi_config = {
        .sta = {
#if !CONFIG_WIFI_SSID_PWD_FROM_STDIN
            .ssid = CONFIG_WIFI_SSID,
            .password = CONFIG_WIFI_PASSWORD,
#endif
            .scan_method = WIFI_SCAN_METHOD,
            .sort_method = WIFI_CONNECT_AP_SORT_METHOD,
            .threshold.rssi = CONFIG_WIFI_SCAN_RSSI_THRESHOLD,
            .threshold.authmode = WIFI_SCAN_AUTH_MODE_THRESHOLD,
        },
    };
#if CONFIG_WIFI_SSID_PWD_FROM_STDIN
    wifi_configure_stdin_stdout();
    char buf[sizeof(wifi_config.sta.ssid) + sizeof(wifi_config.sta.password) + 2] = {0};
    ESP_LOGI(TAG, "Please input ssid password:");
    fgets(buf, sizeof(buf), stdin);
    int len = strlen(buf);
    buf[len - 1] = '\0'; /* removes '\n' */
    memset(wifi_config.sta.ssid, 0, sizeof(wifi_config.sta.ssid));

    char *rest = NULL;
    char *temp = strtok_r(buf, " ", &rest);
    strncpy((char *)wifi_config.sta.ssid, temp, sizeof(wifi_config.sta.ssid));
    memset(wifi_config.sta.password, 0, sizeof(wifi_config.sta.password));
    temp = strtok_r(NULL, " ", &rest);
    if (temp)
    {
        strncpy((char *)wifi_config.sta.password, temp, sizeof(wifi_config.sta.password));
    }
    else
    {
        wifi_config.sta.threshold.authmode = WIFI_AUTH_OPEN;
    }
#endif
    return wifi_sta_do_connect(wifi_config, true);
}

esp_err_t esp32_wifi_connect(void)
{
    if (wifi_connect() != ESP_OK)
        return ESP_FAIL;

    ESP_ERROR_CHECK(esp_register_shutdown_handler(&wifi_shutdown));
    return ESP_OK;
}
