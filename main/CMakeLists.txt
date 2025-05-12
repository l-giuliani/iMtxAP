set(SOURCES
    "iMtxAP.c"
    "drivers/wifi.cpp"
    "drivers/uart.cpp"
    "webserver/webserver.cpp"
    "webserver/wshelpers.cpp"
    "webserver/libs/wsLibs.cpp"
    "webserver/routes/routes.cpp"
    "services/systemServices.cpp"
    "services/dataServices.cpp"
    "webcontrollers/controllers.cpp"
    "libcomm/protocols/protocolLibs.cpp"
    "libcomm/protocols/protocolsDto.cpp"
    "libcomm/protocols/layers/serialDataLinkLayer.cpp"
    "libcomm/protocols/mtx/mtxDto.cpp"
    "libcomm/protocols/mtx/mtxProtocol.cpp"
    "libcomm/protocols/mtx/layers/mtxLayers.cpp"
)

set(HEADERS_DIR
    "." 
    "drivers"
    "utils"
    "webserver"
    "webserver/libs"
    "webserver/routes"
    "services"
    "webcontrollers"
    "libcomm"
    "libcomm/protocols"
    "libcomm/protocols/layers"
    "libcomm/protocols/mtx"
    "libcomm/protocols/mtx/layers"
)

idf_component_register(SRCS ${SOURCES}
                    PRIV_REQUIRES spi_flash
                    REQUIRES esp_wifi nvs_flash esp_netif esp_event esp_http_server driver
                    INCLUDE_DIRS ${HEADERS_DIR})
