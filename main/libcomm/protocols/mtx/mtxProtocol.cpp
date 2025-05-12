#include "mtxProtocol.h"

NProtocols::MtxProtocol mtxProtocol;

namespace NProtocols {

void MtxProtocol::init(MtxProtInit& initData) {
    NProtocols::NLayers::SerialDLLayer* dllayer = this->getLinkLayer();

    dllayer->setStationId(initData.ser.stationId);
    dllayer->setTimeout(initData.ser.timeout); 
    dllayer->setUart(initData.ser.uart);

    this->initialized = true;
}

NProtocols::NLayers::SerialDLLayer* MtxProtocol::getLinkLayer() {
    return this->mtxAppLayer.getLinkLayer();
}

void MtxProtocol::sendReadFileRequest(uint8_t* buffer, char* filename, uint32_t offset, uint32_t size) {
    if (!this->initialized) {
        return;
    }
    this->mtxAppLayer.sendReadFileRequest(buffer, filename, offset, size);
}
int MtxProtocol::recvReadFileResponse(uint8_t* buffer, uint8_t** data, uint32_t& len) {
    if (!this->initialized) {
        return -1;
    }
    return this->mtxAppLayer.recvReadFileResponse(buffer, data, len);
}
void MtxProtocol::sendWriteFileRequest(uint8_t* buffer, char* filename, uint8_t* data, uint32_t offset, uint32_t size) {
    if (!this->initialized) {
        return;
    }
    this->mtxAppLayer.sendWriteFileRequest(buffer, filename, data, offset, size);
}
int MtxProtocol::recvWriteFileResponse(uint8_t* buffer) {
    if (!this->initialized) {
        return -1;
    }
    return this->mtxAppLayer.recvWriteFileResponse(buffer);
}

}