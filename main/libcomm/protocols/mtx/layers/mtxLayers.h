#ifndef _MTXLAYERS_H_
#define _MTXLAYERS_H_

#include <cstdint>
#include "serialDataLinkLayer.h"
#include "mtxDto.h"

namespace NProtocols {
namespace NLayers {

class MtxPresLayer {
private:
    SerialDLLayer serialDLLayer;
public:
    NProtocols::NLayers::SerialDLLayer* getLinkLayer();
    void sendReadFileRequest(NProtocols::NDto::NEncoders::MtxAppLayerMessage& mtxAppMessage, uint8_t* buffer);
    int recvReadFileResponse(uint8_t* buffer, NProtocols::NDto::NDecoders::MtxPresLayerMessage& message);
    void sendWriteFileRequest(NProtocols::NDto::NEncoders::MtxAppLayerMessage& mtxAppMessage, uint8_t* buffer, uint8_t* data, uint32_t size);
    int recvWriteFileResponse(uint8_t* buffer, NProtocols::NDto::NDecoders::MtxPresLayerMessage& message);
};

class MtxAppLayer {
private:
MtxPresLayer mtxPresLayer;
public:
    NProtocols::NLayers::SerialDLLayer* getLinkLayer();
    void sendReadFileRequest(uint8_t* buffer, char* filename, uint32_t offset, uint32_t size);
    int recvReadFileResponse(uint8_t* buffer, uint8_t** data, uint32_t& len);
    void sendWriteFileRequest(uint8_t* buffer, char* filename, uint8_t* data, uint32_t offset, uint32_t size);
    int recvWriteFileResponse(uint8_t* buffer);
};

}
}

#endif // _MTXLAYERS_H