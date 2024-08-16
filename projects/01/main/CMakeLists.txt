idf_component_register(SRCS "01.c"
                    INCLUDE_DIRS ".")
spiffs_create_partition_image(storage ../files FLASH_IN_PROJECT)
