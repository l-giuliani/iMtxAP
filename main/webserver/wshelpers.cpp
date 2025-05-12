#include "wshelpers.h"

#include "wifi.h"

namespace NWebServer {

void WiFiNetworkInterface::initAndStart() {
    NDrivers::WifiAP::initAndStart();
}

void WiFiNetworkInterface::stop() {

}

}