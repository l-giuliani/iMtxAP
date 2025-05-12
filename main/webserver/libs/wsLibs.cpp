#include "wsLibs.h"

namespace NWebServer {
namespace NLibs {
    
    /**
     * @return -1 error, 1 ok
     */
    int WsLibs::readBody(httpd_req_t *req, uint8_t* buffer, uint32_t chunkSize) {
        int remaining = chunkSize;
        int ret;
        while (remaining > 0) {
            ret = httpd_req_recv(req, (char*)(&buffer[chunkSize - remaining]), remaining);
            if (ret <= 0) {
                return -1;
            }
            remaining -= ret;
        }
        return 1;
    }

}
}