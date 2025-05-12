#ifndef _DATASERVICES_H_
#define _DATASERVICES_H_

#include <cstdint>
#include "esp_http_server.h"

using ChunkEndpoint = void (*) (httpd_req_t *b_req, uint8_t* chunk, uint32_t chunkLen);

namespace NDataServices {

    class Services {
    private:
    public:
        static int readFile(httpd_req_t *b_req, char* filename, uint32_t offset, uint32_t size, ChunkEndpoint chunkEndpoint);
        static int writeFile(char* filename, uint8_t* data, uint32_t offset, uint32_t size);
    };
}

#endif // _DATASERVICES_H