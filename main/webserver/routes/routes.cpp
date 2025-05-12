#include "routes.h"

namespace NWebServer {
    namespace NRoutes {

        Routes::Routes() {
            this->nRoutes = 0;
            memset(this->routeList, 0, sizeof(this->routeList));
        }

        void Routes::action(httpd_method_t method, char* path, ws_http_handler handler) {
            if(this->nRoutes >= MAX_ROUTES) {
                return;
            }
            this->routeList[this->nRoutes].uri = path;
            this->routeList[this->nRoutes].method = method;
            this->routeList[this->nRoutes].handler = handler; 
            this->routeList[this->nRoutes].user_ctx  = nullptr;
            this->nRoutes++;
        }

        void Routes::get(char* path, ws_http_handler handler) {
            this->action(HTTP_GET, path, handler);
        }

        void Routes::post(char* path, ws_http_handler handler) {
            this->action(HTTP_POST, path, handler);
        }

        NUtils::SimpleListIterator<httpd_uri_t> Routes::getSimpleIterator(Routes* routes) {
            NUtils::SimpleListIterator<httpd_uri_t> sit(routes);
            return sit;
        }

        void* Routes::getListElements() {
            return ((void*)&this->routeList[0]);
        }

        uint16_t Routes::getNElements() {
            return this->nRoutes;
        }

    }
}