#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include <cstdint>
#include "wshelpers.h"
#include "routes.h"

namespace NWebServer {
    
    class WebServer {
    private:
        NetworkInterface* networkInterface;
        uint16_t serverPort;
    public:
        WebServer(NetworkInterface* networkInterface, uint16_t serverPort);
        void initAndStart(NWebServer::NRoutes::Routes& routes);
    }; 
}

#endif // _WEBSERVER_H