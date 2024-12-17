set(component_srcs "src/rgb_led_strip.c")

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS "inc"
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES "driver"
                       REQUIRES "")
idf_component_register(SRCS "led_strip_rmt_ws2812.c"
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES "driver"
                    )