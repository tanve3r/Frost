set(component_srcs "src/restart.c")

idf_component_register(SRCS "${component_srcs}"
                       INCLUDE_DIRS "inc"
                       PRIV_INCLUDE_DIRS ""
                       PRIV_REQUIRES ""
                       REQUIRES "")
