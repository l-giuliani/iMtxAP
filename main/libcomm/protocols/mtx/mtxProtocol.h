#ifndef _MTXPROTOCOL_H_
#define _MTXPROTOCOL_H_

#include "mtxLayers.h"
#include "uart.h"
#include "serialDataLinkLayer.h"

#define MAX_FILE_READ_LEN  255
#define MAX_FILE_WRITE_LEN  255

namespace NProtocols {

namespace NLibs {

    namespace MTX_COMMANDS {
    enum commands {
        COMMAND_DATA = 8,
        COMMAND_READ_FILE = 24,
        COMMAND_WRITE_FILE = 32,
        COMMAND_FOLDER_CONTENT = 15,
        N_COMMANDS = 5
    };
    } 

}

typedef struct {
    struct {
        uint16_t stationId;
        NDrivers::Uart* uart;
        uint32_t timeout;
    } ser;
} MtxProtInit;

class MtxProtocol {
private:
    bool initialized = false;
    NProtocols::NLayers::MtxAppLayer mtxAppLayer;
public:
    void init(MtxProtInit& initData);
    NProtocols::NLayers::SerialDLLayer* getLinkLayer();
    void sendReadFileRequest(uint8_t* buffer, char* filename, uint32_t offset, uint32_t size);
    int recvReadFileResponse(uint8_t* buffer, uint8_t** data, uint32_t& len);
    void sendWriteFileRequest(uint8_t* buffer, char* filename, uint8_t* data, uint32_t offset, uint32_t size);
    int recvWriteFileResponse(uint8_t* buffer);
};

}

#endif // _MTXPROTOCOL_H