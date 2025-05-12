#ifndef _DRIVER_WIFI_H_
#define _DRIVER_WIFI_H_


#include <stdint.h>
#include "esp_wifi.h"

#ifdef __cplusplus

namespace NDrivers {
    
    class WifiAP {
    private:
        static char* ssid;
        static uint16_t channel;
        static char* password;
        static uint16_t max_connection;
        static wifi_auth_mode_t authmode;

        static void initNvsFlash();

    public:
        static void initAndStart();
    };

}

extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif