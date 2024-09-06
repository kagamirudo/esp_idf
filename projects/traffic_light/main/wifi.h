#ifndef WIFI_H
#define WIFI_H

#include "esp_err.h"
#include "esp_wifi_types.h"
#include "esp_event_base.h"

// Configuration macros
#if !CONFIG_IDF_TARGET_LINUX && CONFIG_CONNECT_WIFI
#define NETIF_DESC_STA "wifi_netif_sta"
#endif

#if CONFIG_CONNECT_ETHERNET
#define NETIF_DESC_ETH "wifi_netif_eth"
#endif

#if CONFIG_CONNECT_PPP
#define NETIF_DESC_PPP "wifi_netif_ppp"
#endif

#if CONFIG_WIFI_SCAN_METHOD_FAST
#define WIFI_SCAN_METHOD WIFI_FAST_SCAN
#elif CONFIG_WIFI_SCAN_METHOD_ALL_CHANNEL
#define WIFI_SCAN_METHOD WIFI_ALL_CHANNEL_SCAN
#endif

#if CONFIG_WIFI_CONNECT_AP_BY_SIGNAL
#define WIFI_CONNECT_AP_SORT_METHOD WIFI_CONNECT_AP_BY_SIGNAL
#elif CONFIG_WIFI_CONNECT_AP_BY_SECURITY
#define WIFI_CONNECT_AP_SORT_METHOD WIFI_CONNECT_AP_BY_SECURITY
#endif

#if CONFIG_WIFI_AUTH_OPEN
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
#elif CONFIG_WIFI_AUTH_WEP
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WEP
#elif CONFIG_WIFI_AUTH_WPA_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_PSK
#elif CONFIG_WIFI_AUTH_WPA2_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK
#elif CONFIG_WIFI_AUTH_WPA_WPA2_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK
#elif CONFIG_WIFI_AUTH_WPA2_ENTERPRISE
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_ENTERPRISE
#elif CONFIG_WIFI_AUTH_WPA3_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA3_PSK
#elif CONFIG_WIFI_AUTH_WPA2_WPA3_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_WPA3_PSK
#elif CONFIG_WIFI_AUTH_WAPI_PSK
#define WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WAPI_PSK
#endif

// Function declarations
void wifi_stop(void);
void wifi_start(void);
void wifi_shutdown(void);

esp_err_t wifi_connect(void);
esp_err_t esp32_wifi_connect(void);
esp_err_t wifi_sta_do_disconnect(void);
esp_err_t wifi_sta_do_connect(wifi_config_t wifi_config, bool wait);

// Event handler declarations
void wifi_handler_on_sta_got_ip(void *arg, esp_event_base_t event_base,
                                int32_t event_id, void *event_data);
void handler_on_wifi_disconnect(void *arg, esp_event_base_t event_base,
                                int32_t event_id, void *event_data);
void wifi_handler_on_wifi_connect(void *esp_netif, esp_event_base_t event_base,
                                  int32_t event_id, void *event_data);

#endif // WIFI_H