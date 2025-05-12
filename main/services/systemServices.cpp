#include "systemServices.h"

#include <cstdint>

#include "appconf.h"
#include "wshelpers.h"
#include "controllers.h"
#include "routes.h"
#include "webserver.h"
#include "mtxProtocol.h"

NDrivers::Uart uart;
extern NProtocols::MtxProtocol mtxProtocol;

namespace NSystemServices {

    void NetworkServices::initWebServer() {
        NWebServer::WiFiNetworkInterface wifiNI;

        NWebServer::NRoutes::Routes routes;
        NWebControllers::AppController::setup(routes);

        NWebServer::WebServer ws(&wifiNI, (uint16_t)HTTP_SERVER_PORT);
        ws.initAndStart(routes);
    }

    void Services::initSystem() {
        NProtocols::MtxProtInit initdata;
        initdata.ser.stationId = 0xFFFF;
        initdata.ser.timeout = UART_TIMEOUT;

        uart.init(UART_NUM);
        initdata.ser.uart = &uart;

        mtxProtocol.init(initdata);
    }

}

void initWebServer() {
    NSystemServices::NetworkServices::initWebServer();
}

void initSystem() {
    NSystemServices::Services::initSystem();
}