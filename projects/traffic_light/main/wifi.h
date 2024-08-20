static void handler_on_wifi_disconnect(void *arg, esp_event_base_t event_base,
                                       int32_t event_id, void *event_data);
static void wifi_handler_on_wifi_connect(void *esp_netif, esp_event_base_t event_base,
                                         int32_t event_id, void *event_data);
static void wifi_handler_on_sta_got_ip(void *arg, esp_event_base_t event_base,
                                       int32_t event_id, void *event_data);
void wifi_start(void);
void wifi_stop(void);
esp_err_t wifi_sta_do_connect(wifi_config_t wifi_config, bool wait);
esp_err_t wifi_sta_do_disconnect(void);
void wifi_shutdown(void);
esp_err_t wifi_connect(void);
esp_err_t esp32_wifi_connect(void);