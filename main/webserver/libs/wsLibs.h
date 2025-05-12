#ifndef _WSLIBS_H_
#define _WSLIBS_H_

#include <cstdint>
#include "esp_http_server.h"

namespace NWebServer {
namespace NLibs {

    class WsLibs {
    public:
        static int readBody(httpd_req_t *req, uint8_t* buffer, uint32_t chunkSize);
    };

}
}

#endif // _WSLIBS_H