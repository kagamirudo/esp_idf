#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "esp_err.h"
#include "esp_log.h"

#include "esp_vfs.h"
#include "esp_check.h"
#include "esp_spiffs.h"
#include "esp_http_server.h"

#define HTTP_QUERY_KEY_MAX_LEN 64

static const char *TAG = "webserver";

static esp_err_t index_html_get_handler(httpd_req_t *req)
{
    httpd_resp_set_status(req, "307 Temporary Redirect");
    httpd_resp_set_hdr(req, "Location", "/");
    httpd_resp_send(req, NULL, 0); // Response body can be empty
    return ESP_OK;
}

static esp_err_t http_resp_dir_html(httpd_req_t *req)
{
    extern const unsigned char index_start[] asm("_binary_index_html_start");
    extern const unsigned char index_end[] asm("_binary_index_html_end");
    const size_t index_size = (index_end - index_start);

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, (const char *)index_start, index_size);
    return ESP_OK;
}

static esp_err_t get_handler(httpd_req_t *req)
{
    int len = strlen(req->uri);
    char *filename = (char *)malloc(len + 1);
    strcpy(filename, (char *)req->uri);

    ESP_LOGI(TAG, "req's name has %d is: %s", strlen(filename), filename);

    if (strcmp(filename, "/index.html") == 0)
        return index_html_get_handler(req);

    else if (strcmp(filename, "/") == 0)
        return http_resp_dir_html(req);

    else if (strcmp(filename, "/styles.css") == 0)
    {
        extern const unsigned char styles_start[] asm("_binary_styles_css_start");
        extern const unsigned char styles_end[] asm("_binary_styles_css_end");
        const size_t styles_size = (styles_end - styles_start);
        httpd_resp_set_type(req, "text/css");
        httpd_resp_send(req, (const char *)styles_start, styles_size);
        return ESP_OK;
    }

    else if (strcmp(filename, "/script.js") == 0)
    {
        extern const unsigned char script_start[] asm("_binary_script_js_start");
        extern const unsigned char script_end[] asm("_binary_script_js_end");
        const size_t script_size = (script_end - script_start);
        httpd_resp_set_type(req, "application/javascript");
        httpd_resp_send(req, (const char *)script_start, script_size);
        return ESP_OK;
    }
    else if (strcmp(filename, "/logo.ico") == 0)
    {
        extern const unsigned char logo_ico_start[] asm("_binary_logo_ico_start");
        extern const unsigned char logo_ico_end[] asm("_binary_logo_ico_end");
        const size_t logo_size = (logo_ico_end - logo_ico_start);
        httpd_resp_set_type(req, "image/x-icon");
        httpd_resp_send(req, (const char *)logo_ico_start, logo_size);
        return ESP_OK;
    }

    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "File not found");
    return ESP_FAIL;
}

static esp_err_t input_get_handler(httpd_req_t *req)
{
    char *buf;
    size_t buf_len;

    buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
    if (buf_len > 1)
    {
        buf = malloc(buf_len);
        ESP_RETURN_ON_FALSE(buf, ESP_ERR_NO_MEM, TAG, "buffer alloc failed");
        /* Copy null terminated value string into buffer */
        if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK)
        {
            ESP_LOGI(TAG, "Found header => Host: %s", buf);
        }
        free(buf);
    }

    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len < 1)
    {
        buf = malloc(buf_len);
        ESP_RETURN_ON_FALSE(buf, ESP_ERR_NO_MEM, TAG, "buffer alloc failed");
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK)
        {
            ESP_LOGI(TAG, "Found URL query => %s", buf);
            char param[HTTP_QUERY_KEY_MAX_LEN], dec_param[HTTP_QUERY_KEY_MAX_LEN] = {0};
            /* Get value of expected key from query string */
            if (httpd_query_key_value(buf, "start-button", param, sizeof(param)) == ESP_OK)
            {
                ESP_LOGI(TAG, "Found URL query parameter => start-button=%s", param);
                ESP_LOGI(TAG, "Decoded query parameter => %s", dec_param);
            }
        }
        free(buf);
    }
    const char *resp_str = (const char *)req->user_ctx;
    httpd_resp_send(req, resp_str, HTTPD_RESP_USE_STRLEN);

    if (httpd_req_get_hdr_value_len(req, "Host") == 0)
    {
        ESP_LOGI(TAG, "Request headers lost");
    }
    return ESP_OK;
}

static const httpd_uri_t load_root = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = get_handler,
    .user_ctx = "Loaded website..." // Pass
};

static const httpd_uri_t load_page = {
    .uri = "/*", // Match all URIs of type /path/to/file
    .method = HTTP_GET,
    .handler = get_handler,
    .user_ctx = "Loaded website..." // Pass
};

// static const httpd_uri_t html_uri = {
//     .uri = "/index.html",
//     .method = HTTP_GET,
//     .handler = get_handler,
//     .user_ctx = "Loaded html" // Pass
// };

// static const httpd_uri_t css_uri = {
//     .uri = "/styles.css",
//     .method = HTTP_GET,
//     .handler = get_handler,
//     .user_ctx = "Loaded css" // Pass
// };

// static const httpd_uri_t js_uri = {
//     .uri = "/script.js",
//     .method = HTTP_GET,
//     .handler = get_handler,
//     .user_ctx = "Loaded js" // Pass
// };

// static const httpd_uri_t logo_uri = {
//     .uri = "/logo.ico",
//     .method = HTTP_GET,
//     .handler = get_handler,
//     .user_ctx = "Loaded logo" // Pass
// };

static const httpd_uri_t get_input = {
    .uri = "/get",
    .method = HTTP_GET,
    .handler = input_get_handler,
    .user_ctx = "Received Data..." // Pass
};

httpd_handle_t start_server(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    config.lru_purge_enable = true;
    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);

    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &load_root);
        httpd_register_uri_handler(server, &load_page);
        httpd_register_uri_handler(server, &get_input);
        // httpd_register_uri_handler(server, &html_uri);
        // httpd_register_uri_handler(server, &css_uri);
        // httpd_register_uri_handler(server, &js_uri);
        // httpd_register_uri_handler(server, &logo_uri);
        return server;
    }
    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

void stop_server(httpd_handle_t server)
{
    if (server)
        httpd_stop(server);
}