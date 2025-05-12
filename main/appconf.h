#ifndef _APPCONF_H_
#define _APPCONF_H_

#include "esp_wifi.h"
#include "driver/uart.h"

#define ESP_WIFI_SSID       "iMtx"
#define ESP_WIFI_CHANNEL    1  
#define ESP_WIFI_PASS       "password"
#define MAX_STA_CONN        1
#define WIFI_AUTHMODE       WIFI_AUTH_WPA2_PSK

#define HTTP_SERVER_PORT    4000
#define HTTP_MAX_BODY_LEN   4096

#define UART_NUM            UART_NUM_1
#define UART_TX_PIN         7       
#define UART_RX_PIN         6
#define UART_BAUDRATE       115200
#define UART_DATA_BITS      UART_DATA_8_BITS
#define UART_PARITY         UART_PARITY_DISABLE
#define UART_STOP_BITS      UART_STOP_BITS_1
#define UART_FLOW_CONTROL   UART_HW_FLOWCTRL_DISABLE
#define UART_TIMEOUT        2000

#endif // _APPCONF_H

