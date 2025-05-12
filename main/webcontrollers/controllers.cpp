#include "controllers.h"

#include <cstdlib>
#include "esp_http_server.h"
#include "appconf.h"
#include "dataServices.h"
#include "wsLibs.h"

uint8_t g_body[HTTP_MAX_BODY_LEN];

namespace NWebControllers {

    void AppController::setup(NWebServer::NRoutes::Routes& routes) {

        routes.get((char*)"/test", [](httpd_req_t *req) -> esp_err_t {
            const char* resp_str = "Hello World!";
            httpd_resp_send(req, resp_str, HTTPD_RESP_USE_STRLEN);
            return ESP_OK;  
        });

        routes.get((char*)"/file", [](httpd_req_t *req) -> esp_err_t {
            char query[128];
            char filename[64];
            char offset_str[16];
            char size_str[16];

            if (httpd_req_get_url_query_str(req, query, sizeof(query)) != ESP_OK) {
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "No query string");
                return ESP_ERR_HTTPD_RESP_HDR;
            }

            if (httpd_query_key_value(query, "filename", filename, sizeof(filename)) != ESP_OK ||
                    httpd_query_key_value(query, "offset", offset_str, sizeof(offset_str)) != ESP_OK ||
                    httpd_query_key_value(query, "size", size_str, sizeof(size_str)) != ESP_OK) {
                        
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Missing query param");
                return ESP_ERR_HTTPD_RESP_HDR;
            }

            char* end;
            int offset = std::strtol(offset_str, &end, 10);
            if (*end != '\0') {
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Value Error");
                return ESP_ERR_HTTPD_RESP_HDR;
            }
            int size = std::strtol(size_str, &end, 10);
            if (*end != '\0') {
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Value Error");
                return ESP_ERR_HTTPD_RESP_HDR;
            }
            
            int res = NDataServices::Services::readFile(req, filename, offset, size, [](httpd_req_t *b_req, uint8_t* chunk, uint32_t chunkLen) -> void {
                httpd_resp_send_chunk(b_req, (const char *)chunk, chunkLen);
            });
            if (res != 1) {
                httpd_resp_sendstr_chunk(req,"\nERROR");
                return ESP_FAIL;
            }
            
            httpd_resp_send_chunk(req, NULL, 0);

            return ESP_OK;
        });
        
        routes.post((char*)"/file", [](httpd_req_t *req) -> esp_err_t {
            char query[128];
            char filename[64];
            char offset_str[16];

            if(req->content_len >= HTTP_MAX_BODY_LEN) {
                httpd_resp_send_err(req, HTTPD_413_CONTENT_TOO_LARGE, "Body size");
                return ESP_ERR_HTTPD_RESP_HDR;
            }

            if (httpd_req_get_url_query_str(req, query, sizeof(query)) != ESP_OK) {
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "No query string");
                return ESP_ERR_HTTPD_RESP_HDR;
            }

            if (httpd_query_key_value(query, "filename", filename, sizeof(filename)) != ESP_OK ||
                    httpd_query_key_value(query, "offset", offset_str, sizeof(offset_str)) != ESP_OK) {
                        
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Missing query param");
                return ESP_ERR_HTTPD_RESP_HDR;
            }

            char* end;
            int offset = std::strtol(offset_str, &end, 10);
            if (*end != '\0') {
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Value Error");
                return ESP_ERR_HTTPD_RESP_HDR;
            }

            /*
             *  Actually I read all the body in ram and I allow only small bodies to be sended.
             *   It may change in future, the body could be read in chunk.
            */
            int res = NWebServer::NLibs::WsLibs::readBody(req, g_body, req->content_len);
            if(res == -1) {
                httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Error body");
                return ESP_ERR_HTTPD_RESP_HDR;
            }

            /*for(int i=0;i<req->content_len;i++){
                uint8_t low = g_body[i] & 0x0F;
                uint8_t high = g_body[i] >> 4;
                char num[2];
                num[0] = high < 10 ? ('0' + high) : ('A' + high - 10);
                num[1] = low < 10 ? ('0' + low) : ('A' + low - 10);
                httpd_resp_send_chunk(req, (const char *)num, 2);
            }
            httpd_resp_send_chunk(req, NULL, 0);
            return ESP_OK;*/
            
            res = NDataServices::Services::writeFile(filename, g_body, offset, req->content_len);
            if(res == -1) {
                httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Error writing");
                return ESP_FAIL;
            }

            httpd_resp_set_status(req, "201 Created");
            httpd_resp_send(req, NULL, 0);
        
            return ESP_OK;
        });
    }

}