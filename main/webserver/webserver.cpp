#include "webserver.h"

#include "esp_http_server.h"

namespace NWebServer {
    
    WebServer::WebServer(NetworkInterface* networkInterface, uint16_t serverPort) {
        this->networkInterface = networkInterface;
        this->serverPort = serverPort;
    }

    void WebServer::initAndStart(NWebServer::NRoutes::Routes& routes) {
        this->networkInterface->initAndStart();

        httpd_config_t config = HTTPD_DEFAULT_CONFIG();
        config.stack_size = 8192;
        config.server_port = this->serverPort;

        NUtils::SimpleListIterator<httpd_uri_t> sit = NWebServer::NRoutes::Routes::getSimpleIterator(&routes);
        sit.begin();

        httpd_handle_t server = nullptr;
        ESP_ERROR_CHECK(httpd_start(&server, &config));
        httpd_uri_t* el;
        while ((el = sit.next()) != nullptr) {
            httpd_register_uri_handler(server, el);
        }
    }

}