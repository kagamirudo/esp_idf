#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_check.h"
#include "esp_spiffs.h"
#include "esp_http_server.h"

#include "light_control.h"

#define HTTP_QUERY_KEY_MAX_LEN 64
#define MAX_TIMEOUTS 3

static const char *TAG = "traffic_light_webserver";

extern bool run;

// Function prototypes
static esp_err_t index_html_get_handler(httpd_req_t *req);
static esp_err_t http_resp_dir_html(httpd_req_t *req);
static esp_err_t get_handler(httpd_req_t *req);
static esp_err_t serve_file(httpd_req_t *req, const char *filename, const char *content_type);
static esp_err_t input_get_handler(httpd_req_t *req);

// Embedded file declarations
#define DECLARE_EMBEDDED_FILE(name) \
    extern const unsigned char _binary_##name##_start[] asm("_binary_" #name "_start"); \
    extern const unsigned char _binary_##name##_end[] asm("_binary_" #name "_end")

DECLARE_EMBEDDED_FILE(index_html);
DECLARE_EMBEDDED_FILE(styles_css);
DECLARE_EMBEDDED_FILE(script_js);
DECLARE_EMBEDDED_FILE(logo_ico);

// Helper function to serve static files
static esp_err_t serve_file(httpd_req_t *req, const char *filename, const char *content_type)
{
    const unsigned char *file_start;
    const unsigned char *file_end;

    if (strcmp(filename, "index_html") == 0)
    {
        file_start = _binary_index_html_start;
        file_end = _binary_index_html_end;
    }
    else if (strcmp(filename, "styles_css") == 0)
    {
        file_start = _binary_styles_css_start;
        file_end = _binary_styles_css_end;
    }
    else if (strcmp(filename, "script_js") == 0)
    {
        file_start = _binary_script_js_start;
        file_end = _binary_script_js_end;
    }
    else if (strcmp(filename, "logo_ico") == 0)
    {
        file_start = _binary_logo_ico_start;
        file_end = _binary_logo_ico_end;
    }
    else
    {
        return ESP_ERR_NOT_FOUND;
    }

    const size_t file_size = (file_end - file_start);
    httpd_resp_set_type(req, content_type);
    return httpd_resp_send(req, (const char *)file_start, file_size);
}

static esp_err_t index_html_get_handler(httpd_req_t *req)
{
    httpd_resp_set_status(req, "307 Temporary Redirect");
    httpd_resp_set_hdr(req, "Location", "/");
    return httpd_resp_send(req, NULL, 0);
}

static esp_err_t http_resp_dir_html(httpd_req_t *req)
{
    return serve_file(req, "index_html", "text/html");
}

static esp_err_t get_handler(httpd_req_t *req)
{
    char *filename = (char *)malloc(strlen(req->uri) + 1);
    if (!filename)
    {
        return ESP_ERR_NO_MEM;
    }
    strcpy(filename, req->uri);

    ESP_LOGI(TAG, "Request for: %s", filename);

    esp_err_t result;
    if (strcmp(filename, "/index.html") == 0)
    {
        result = index_html_get_handler(req);
    }
    else if (strcmp(filename, "/") == 0)
    {
        result = http_resp_dir_html(req);
    }
    else if (strcmp(filename, "/styles.css") == 0)
    {
        result = serve_file(req, "styles_css", "text/css");
    }
    else if (strcmp(filename, "/script.js") == 0)
    {
        result = serve_file(req, "script_js", "application/javascript");
    }
    else if (strcmp(filename, "/logo.ico") == 0)
    {
        result = serve_file(req, "logo_ico", "image/x-icon");
    }
    else
    {
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "File not found");
        result = ESP_FAIL;
    }

    free(filename);
    return result;
}

static esp_err_t input_get_handler(httpd_req_t *req)
{
    char *buf;
    size_t buf_len;
    char param[HTTP_QUERY_KEY_MAX_LEN];
    float timeouts[MAX_TIMEOUTS] = {0};
    const char *timeout_keys[] = {"red-timeout", "yellow-timeout", "green-timeout"};
    char resp_buf[200]; // Increased buffer size for longer responses

    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len > 1)
    {
        buf = malloc(buf_len);
        if (buf == NULL) {
            ESP_LOGE(TAG, "buffer alloc failed");
            return ESP_ERR_NO_MEM;
        }
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK)
        {
            ESP_LOGI(TAG, "Found URL query => %s", buf);

            for (int i = 0; i < MAX_TIMEOUTS; i++)
            {
                if (httpd_query_key_value(buf, timeout_keys[i], param, sizeof(param)) == ESP_OK)
                {
                    timeouts[i] = atof(param);
                    ESP_LOGI(TAG, "%s: %.2f", timeout_keys[i], timeouts[i]);
                }
            }

            if (httpd_query_key_value(buf, "stop-button", param, sizeof(param)) == ESP_OK)
            {
                ESP_LOGI(TAG, "Stop button pressed");
                // Turn off all LEDs
                for (size_t i = 0; i < light_count; i++)
                {
                    led_control(traffic_lights[i], false);
                }
                snprintf(resp_buf, sizeof(resp_buf), "Traffic light stopped");
                run = false;
            }
            else
            {
                // Assume it's a start action if it's not a stop action
                ESP_LOGI(TAG, "Start button pressed");
                // Update the global timeouts
                for (int i = 0; i < MAX_TIMEOUTS; i++)
                {
                    traffic_light_timeout[i] = timeouts[MAX_TIMEOUTS - i - 1];
                }
                snprintf(resp_buf, sizeof(resp_buf),
                         "Traffic light started with timeouts: Red=%.2f, Yellow=%.2f, Green=%.2f",
                         timeouts[0], timeouts[1], timeouts[2]);
                run = true;
            }
        }
        free(buf);
    }
    else
    {
        snprintf(resp_buf, sizeof(resp_buf), "No query parameters received");
    }

    return httpd_resp_send(req, resp_buf, HTTPD_RESP_USE_STRLEN);
}

static const httpd_uri_t uri_handlers[] = {
    {.uri = "/", .method = HTTP_GET, .handler = get_handler, .user_ctx = "Loaded website..."},
    {.uri = "/*", .method = HTTP_GET, .handler = get_handler, .user_ctx = "Loaded website..."},
    {.uri = "/get", .method = HTTP_GET, .handler = input_get_handler, .user_ctx = "Received Data..."},
    {.uri = "/index.html", .method = HTTP_GET, .handler = get_handler, .user_ctx = "Loaded html"},
    {.uri = "/styles.css", .method = HTTP_GET, .handler = get_handler, .user_ctx = "Loaded css"},
    {.uri = "/script.js", .method = HTTP_GET, .handler = get_handler, .user_ctx = "Loaded js"},
    {.uri = "/logo.ico", .method = HTTP_GET, .handler = get_handler, .user_ctx = "Loaded logo"}};

httpd_handle_t start_server(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    config.lru_purge_enable = true;
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);

    if (httpd_start(&server, &config) == ESP_OK)
    {
        for (int i = 0; i < sizeof(uri_handlers) / sizeof(uri_handlers[0]); i++)
        {
            httpd_register_uri_handler(server, &uri_handlers[i]);
        }
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

void stop_server(httpd_handle_t server)
{
    if (server)
    {
        httpd_stop(server);
    }
}
