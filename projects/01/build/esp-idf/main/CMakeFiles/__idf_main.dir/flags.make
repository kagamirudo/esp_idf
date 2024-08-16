# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# compile C with /home/kagamirudo/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20240530/xtensa-esp-elf/bin/xtensa-esp32-elf-gcc
C_DEFINES = -DESP_PLATFORM -DIDF_VER=\"0331b167-dirty\" -DMBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\" -DSOC_MMU_PAGE_SIZE=CONFIG_MMU_PAGE_SIZE -DSOC_XTAL_FREQ_MHZ=CONFIG_XTAL_FREQ -DUNITY_INCLUDE_CONFIG_H -D_GLIBCXX_HAVE_POSIX_SEMAPHORE -D_GLIBCXX_USE_POSIX_SEMAPHORE -D_GNU_SOURCE -D_POSIX_READER_WRITER_LOCKS

C_INCLUDES = -I/home/kagamirudo/esp-idf/projects/01/build/config -I/home/kagamirudo/esp-idf/projects/01/main -I/home/kagamirudo/esp-idf/components/newlib/platform_include -I/home/kagamirudo/esp-idf/components/freertos/config/include -I/home/kagamirudo/esp-idf/components/freertos/config/include/freertos -I/home/kagamirudo/esp-idf/components/freertos/config/xtensa/include -I/home/kagamirudo/esp-idf/components/freertos/FreeRTOS-Kernel/include -I/home/kagamirudo/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include -I/home/kagamirudo/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos -I/home/kagamirudo/esp-idf/components/freertos/esp_additions/include -I/home/kagamirudo/esp-idf/components/esp_hw_support/include -I/home/kagamirudo/esp-idf/components/esp_hw_support/include/soc -I/home/kagamirudo/esp-idf/components/esp_hw_support/include/soc/esp32 -I/home/kagamirudo/esp-idf/components/esp_hw_support/dma/include -I/home/kagamirudo/esp-idf/components/esp_hw_support/ldo/include -I/home/kagamirudo/esp-idf/components/esp_hw_support/debug_probe/include -I/home/kagamirudo/esp-idf/components/esp_hw_support/port/esp32/. -I/home/kagamirudo/esp-idf/components/esp_hw_support/port/esp32/include -I/home/kagamirudo/esp-idf/components/heap/include -I/home/kagamirudo/esp-idf/components/log/include -I/home/kagamirudo/esp-idf/components/soc/include -I/home/kagamirudo/esp-idf/components/soc/esp32 -I/home/kagamirudo/esp-idf/components/soc/esp32/include -I/home/kagamirudo/esp-idf/components/hal/platform_port/include -I/home/kagamirudo/esp-idf/components/hal/esp32/include -I/home/kagamirudo/esp-idf/components/hal/include -I/home/kagamirudo/esp-idf/components/esp_rom/include -I/home/kagamirudo/esp-idf/components/esp_rom/esp32/include -I/home/kagamirudo/esp-idf/components/esp_rom/esp32/include/esp32 -I/home/kagamirudo/esp-idf/components/esp_rom/esp32 -I/home/kagamirudo/esp-idf/components/esp_common/include -I/home/kagamirudo/esp-idf/components/esp_system/include -I/home/kagamirudo/esp-idf/components/esp_system/port/soc -I/home/kagamirudo/esp-idf/components/esp_system/port/include/private -I/home/kagamirudo/esp-idf/components/xtensa/esp32/include -I/home/kagamirudo/esp-idf/components/xtensa/include -I/home/kagamirudo/esp-idf/components/xtensa/deprecated_include -I/home/kagamirudo/esp-idf/components/lwip/include -I/home/kagamirudo/esp-idf/components/lwip/include/apps -I/home/kagamirudo/esp-idf/components/lwip/include/apps/sntp -I/home/kagamirudo/esp-idf/components/lwip/lwip/src/include -I/home/kagamirudo/esp-idf/components/lwip/port/include -I/home/kagamirudo/esp-idf/components/lwip/port/freertos/include -I/home/kagamirudo/esp-idf/components/lwip/port/esp32xx/include -I/home/kagamirudo/esp-idf/components/lwip/port/esp32xx/include/arch -I/home/kagamirudo/esp-idf/components/lwip/port/esp32xx/include/sys -I/home/kagamirudo/esp-idf/components/esp_driver_gpio/include -I/home/kagamirudo/esp-idf/components/esp_pm/include -I/home/kagamirudo/esp-idf/components/mbedtls/port/include -I/home/kagamirudo/esp-idf/components/mbedtls/mbedtls/include -I/home/kagamirudo/esp-idf/components/mbedtls/mbedtls/library -I/home/kagamirudo/esp-idf/components/mbedtls/esp_crt_bundle/include -I/home/kagamirudo/esp-idf/components/mbedtls/mbedtls/3rdparty/everest/include -I/home/kagamirudo/esp-idf/components/mbedtls/mbedtls/3rdparty/p256-m -I/home/kagamirudo/esp-idf/components/mbedtls/mbedtls/3rdparty/p256-m/p256-m -I/home/kagamirudo/esp-idf/components/esp_app_format/include -I/home/kagamirudo/esp-idf/components/esp_bootloader_format/include -I/home/kagamirudo/esp-idf/components/app_update/include -I/home/kagamirudo/esp-idf/components/bootloader_support/include -I/home/kagamirudo/esp-idf/components/bootloader_support/bootloader_flash/include -I/home/kagamirudo/esp-idf/components/esp_partition/include -I/home/kagamirudo/esp-idf/components/efuse/include -I/home/kagamirudo/esp-idf/components/efuse/esp32/include -I/home/kagamirudo/esp-idf/components/esp_mm/include -I/home/kagamirudo/esp-idf/components/spi_flash/include -I/home/kagamirudo/esp-idf/components/pthread/include -I/home/kagamirudo/esp-idf/components/esp_timer/include -I/home/kagamirudo/esp-idf/components/esp_driver_gptimer/include -I/home/kagamirudo/esp-idf/components/esp_ringbuf/include -I/home/kagamirudo/esp-idf/components/esp_driver_uart/include -I/home/kagamirudo/esp-idf/components/vfs/include -I/home/kagamirudo/esp-idf/components/app_trace/include -I/home/kagamirudo/esp-idf/components/esp_event/include -I/home/kagamirudo/esp-idf/components/nvs_flash/include -I/home/kagamirudo/esp-idf/components/esp_driver_pcnt/include -I/home/kagamirudo/esp-idf/components/esp_driver_spi/include -I/home/kagamirudo/esp-idf/components/esp_driver_mcpwm/include -I/home/kagamirudo/esp-idf/components/esp_driver_ana_cmpr/include -I/home/kagamirudo/esp-idf/components/esp_driver_i2s/include -I/home/kagamirudo/esp-idf/components/sdmmc/include -I/home/kagamirudo/esp-idf/components/esp_driver_sdmmc/include -I/home/kagamirudo/esp-idf/components/esp_driver_sdspi/include -I/home/kagamirudo/esp-idf/components/esp_driver_sdio/include -I/home/kagamirudo/esp-idf/components/esp_driver_dac/include -I/home/kagamirudo/esp-idf/components/esp_driver_rmt/include -I/home/kagamirudo/esp-idf/components/esp_driver_tsens/include -I/home/kagamirudo/esp-idf/components/esp_driver_sdm/include -I/home/kagamirudo/esp-idf/components/esp_driver_i2c/include -I/home/kagamirudo/esp-idf/components/esp_driver_ledc/include -I/home/kagamirudo/esp-idf/components/esp_driver_parlio/include -I/home/kagamirudo/esp-idf/components/esp_driver_usb_serial_jtag/include -I/home/kagamirudo/esp-idf/components/driver/deprecated -I/home/kagamirudo/esp-idf/components/driver/i2c/include -I/home/kagamirudo/esp-idf/components/driver/touch_sensor/include -I/home/kagamirudo/esp-idf/components/driver/twai/include -I/home/kagamirudo/esp-idf/components/driver/touch_sensor/esp32/include -I/home/kagamirudo/esp-idf/components/esp_phy/include -I/home/kagamirudo/esp-idf/components/esp_phy/esp32/include -I/home/kagamirudo/esp-idf/components/esp_vfs_console/include -I/home/kagamirudo/esp-idf/components/esp_netif/include -I/home/kagamirudo/esp-idf/components/wpa_supplicant/include -I/home/kagamirudo/esp-idf/components/wpa_supplicant/port/include -I/home/kagamirudo/esp-idf/components/wpa_supplicant/esp_supplicant/include -I/home/kagamirudo/esp-idf/components/esp_coex/include -I/home/kagamirudo/esp-idf/components/esp_wifi/include -I/home/kagamirudo/esp-idf/components/esp_wifi/wifi_apps/include -I/home/kagamirudo/esp-idf/components/esp_wifi/wifi_apps/nan_app/include -I/home/kagamirudo/esp-idf/components/esp_wifi/include/local -I/home/kagamirudo/esp-idf/components/unity/include -I/home/kagamirudo/esp-idf/components/unity/unity/src -I/home/kagamirudo/esp-idf/components/cmock/CMock/src -I/home/kagamirudo/esp-idf/components/console -I/home/kagamirudo/esp-idf/components/http_parser -I/home/kagamirudo/esp-idf/components/esp-tls -I/home/kagamirudo/esp-idf/components/esp-tls/esp-tls-crypto -I/home/kagamirudo/esp-idf/components/esp_adc/include -I/home/kagamirudo/esp-idf/components/esp_adc/interface -I/home/kagamirudo/esp-idf/components/esp_adc/esp32/include -I/home/kagamirudo/esp-idf/components/esp_adc/deprecated/include -I/home/kagamirudo/esp-idf/components/esp_driver_isp/include -I/home/kagamirudo/esp-idf/components/esp_driver_cam/include -I/home/kagamirudo/esp-idf/components/esp_driver_cam/interface -I/home/kagamirudo/esp-idf/components/esp_driver_jpeg/include -I/home/kagamirudo/esp-idf/components/esp_driver_ppa/include -I/home/kagamirudo/esp-idf/components/esp_eth/include -I/home/kagamirudo/esp-idf/components/esp_gdbstub/include -I/home/kagamirudo/esp-idf/components/esp_hid/include -I/home/kagamirudo/esp-idf/components/tcp_transport/include -I/home/kagamirudo/esp-idf/components/esp_http_client/include -I/home/kagamirudo/esp-idf/components/esp_http_server/include -I/home/kagamirudo/esp-idf/components/esp_https_ota/include -I/home/kagamirudo/esp-idf/components/esp_https_server/include -I/home/kagamirudo/esp-idf/components/esp_psram/include -I/home/kagamirudo/esp-idf/components/esp_lcd/include -I/home/kagamirudo/esp-idf/components/esp_lcd/interface -I/home/kagamirudo/esp-idf/components/protobuf-c/protobuf-c -I/home/kagamirudo/esp-idf/components/protocomm/include/common -I/home/kagamirudo/esp-idf/components/protocomm/include/security -I/home/kagamirudo/esp-idf/components/protocomm/include/transports -I/home/kagamirudo/esp-idf/components/protocomm/include/crypto/srp6a -I/home/kagamirudo/esp-idf/components/protocomm/proto-c -I/home/kagamirudo/esp-idf/components/esp_local_ctrl/include -I/home/kagamirudo/esp-idf/components/espcoredump/include -I/home/kagamirudo/esp-idf/components/espcoredump/include/port/xtensa -I/home/kagamirudo/esp-idf/components/wear_levelling/include -I/home/kagamirudo/esp-idf/components/fatfs/diskio -I/home/kagamirudo/esp-idf/components/fatfs/src -I/home/kagamirudo/esp-idf/components/fatfs/vfs -I/home/kagamirudo/esp-idf/components/idf_test/include -I/home/kagamirudo/esp-idf/components/idf_test/include/esp32 -I/home/kagamirudo/esp-idf/components/ieee802154/include -I/home/kagamirudo/esp-idf/components/json/cJSON -I/home/kagamirudo/esp-idf/components/micro_ros_espidf_component/network_interfaces -I/home/kagamirudo/esp-idf/components/micro_ros_espidf_component/micro_ros_src/src/rcl/rcl/include -I/home/kagamirudo/esp-idf/components/mqtt/esp-mqtt/include -I/home/kagamirudo/esp-idf/components/nvs_sec_provider/include -I/home/kagamirudo/esp-idf/components/perfmon/include -I/home/kagamirudo/esp-idf/components/rt/include -I/home/kagamirudo/esp-idf/components/spiffs/include -I/home/kagamirudo/esp-idf/components/wifi_provisioning/include -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/include -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/micro_ros_utilities -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/rcl_logging_interface -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/rcutils -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/rmw -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/rosidl_dynamic_typesupport -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/rosidl_runtime_c -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/rosidl_typesupport_c -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/rosidl_typesupport_interface -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/rosidl_typesupport_introspection_c -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/rosidl_typesupport_microxrcedds_c -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/tracetools -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/ucdr -isystem /home/kagamirudo/esp-idf/components/micro_ros_espidf_component/include/uxr

C_FLAGS = -mlongcalls -Wno-frame-address  -fno-builtin-memcpy -fno-builtin-memset -fno-builtin-bzero -fno-builtin-stpcpy -fno-builtin-strncpy -ffunction-sections -fdata-sections -Wall -Werror=all -Wno-error=unused-function -Wno-error=unused-variable -Wno-error=unused-but-set-variable -Wno-error=deprecated-declarations -Wextra -Wno-error=extra -Wno-unused-parameter -Wno-sign-compare -Wno-enum-conversion -gdwarf-4 -ggdb -Og -fno-shrink-wrap -fmacro-prefix-map=/home/kagamirudo/esp-idf/projects/01=. -fmacro-prefix-map=/home/kagamirudo/esp-idf=/IDF -fstrict-volatile-bitfields -fno-jump-tables -fno-tree-switch-conversion -std=gnu17 -Wno-old-style-declaration

