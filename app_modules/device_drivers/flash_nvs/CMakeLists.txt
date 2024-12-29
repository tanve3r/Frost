set(component_srcs "src/flash_nvs.c")

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS "inc"
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES ""
                       REQUIRES "")
