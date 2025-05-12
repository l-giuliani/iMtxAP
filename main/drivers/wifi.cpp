#include "wifi.h"

#include <cstring>
#include "appconf.h"

#include "esp_flash.h"
#include "esp_mac.h"
#include "esp_event.h"
#include "nvs_flash.h"

namespace NDrivers {

    char* WifiAP::ssid = (char*)ESP_WIFI_SSID;
    uint16_t WifiAP::channel = ESP_WIFI_CHANNEL;
    char* WifiAP::password = (char*)ESP_WIFI_PASS;
    uint16_t WifiAP::max_connection = MAX_STA_CONN;
    wifi_auth_mode_t WifiAP::authmode = WIFI_AUTHMODE;

    void WifiAP::initNvsFlash() {
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
          ESP_ERROR_CHECK(nvs_flash_erase());
          ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);
    }

    void WifiAP::initAndStart() {

        WifiAP::initNvsFlash();

        ESP_ERROR_CHECK(esp_netif_init());
        ESP_ERROR_CHECK(esp_event_loop_create_default());
        esp_netif_create_default_wifi_ap();

        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        ESP_ERROR_CHECK(esp_wifi_init(&cfg));

        wifi_config_t wifi_config = {};
        memcpy(wifi_config.ap.ssid, WifiAP::ssid, strlen(WifiAP::ssid));
        wifi_config.ap.ssid_len = strlen(WifiAP::ssid);
        wifi_config.ap.channel = WifiAP::channel;
        memcpy(wifi_config.ap.password, WifiAP::password, strlen(WifiAP::password));
        wifi_config.ap.max_connection = WifiAP::max_connection;
        wifi_config.ap.authmode = WifiAP::authmode;

        ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
        ESP_ERROR_CHECK(esp_wifi_start());
    }

}