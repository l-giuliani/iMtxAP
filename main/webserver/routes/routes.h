#ifndef _ROUTES_H_
#define _ROUTES_H_

#include <cstdint>
#include "esp_http_server.h"
#include "utils.h"

#define MAX_ROUTES 128

typedef esp_err_t (*ws_http_handler)(httpd_req_t *req);

namespace NWebServer {
    namespace NRoutes {

        class Routes : public NUtils::SimpleIteratorElement {
        private:
            httpd_uri_t routeList[MAX_ROUTES];
            uint16_t nRoutes;
            void action(httpd_method_t method, char* path, ws_http_handler handler);
        public:
            Routes();
            void get(char* path, ws_http_handler handler);
            void post(char* path, ws_http_handler handler);

            static NUtils::SimpleListIterator<httpd_uri_t> getSimpleIterator(Routes* routes);
            void* getListElements();
            uint16_t getNElements();
        };

    }
}

#endif // _ROUTES_H