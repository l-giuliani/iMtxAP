#include "mtxDto.h"

#include <cstring>

namespace NProtocols {
namespace NDto {
namespace NEncoders {

void MtxAppLayerMessage::setCommandCode(uint16_t commandCode) {
    this->commandCode = commandCode;
}

void MtxAppLayerMessage::setMtxReqParams(MessageEncoder* mtxReqParams) {
    this->mtxReqParams = mtxReqParams;
}

void MtxAppLayerMessage::encode(uint8_t* buffer) {
    memcpy(buffer, &commandCode, 2);
    this->mtxReqParams->encode(&buffer[2]);
}

uint32_t MtxAppLayerMessage::getLen() {
    return (sizeof(this->commandCode) + this->mtxReqParams->getLen());
}

void MtxFileRWParams::setOffset(uint16_t offset) {
    this->offset = offset;
}
void MtxFileRWParams::setLen(uint8_t len) {
    this->len = len;
}
void MtxFileRWParams::setFilenameLen(uint8_t filenameLen) {
    this->filenameLen = filenameLen;
}
void MtxFileRWParams::setFilename(char* filename) {
    this->filename = filename;
}
void MtxFileRWParams::encode(uint8_t* buffer) {
    memcpy(buffer, &this->offset, 2);
    buffer[2] = this->len;
    buffer[3] = this->filenameLen;
    memcpy(&buffer[4], this->filename, this->filenameLen);
}
uint32_t MtxFileRWParams::getLen() {
    uint32_t len;
    len = sizeof(this->offset) + sizeof(this->len) + sizeof(this->filenameLen) + this->filenameLen;
    return len;
}

void MtxFileRWPLParams::setBuffer(uint8_t* buffer) {
    this->buffer = buffer;
}
void MtxFileRWPLParams::setLen(uint32_t len) {
    this->len = len;
}
uint32_t MtxFileRWPLParams::getSize() {
    return this->len;
}
void MtxFileRWPLParams::encode(uint8_t* buffer) {
    if(this->len > 0 && this->buffer != nullptr) {
        memcpy(buffer, this->buffer, this->len);
    }
}
uint32_t MtxFileRWPLParams::getLen() {
    return this->len;
}

void MtxPresLayerMessage::setPLParams(MessageEncoder* pLParams) {
    this->pLParams = pLParams;
}
void MtxPresLayerMessage::setLayerMessage(MessageEncoder* layerMessage) {
    this->layerMessage = layerMessage;
}
void MtxPresLayerMessage::encode(uint8_t* buffer) {
    this->layerMessage->encode(buffer);
    this->pLParams->encode(&buffer[this->layerMessage->getLen()]);
}
uint32_t MtxPresLayerMessage::getLen() {
    return (this->pLParams->getLen() + this->layerMessage->getLen());
}

}

namespace NDecoders {
    
    void MtxAppLayerMessage::setCommandCode(uint16_t commandCode) {
        this->commandCode = commandCode;
    }
    uint16_t MtxAppLayerMessage::getCommandCode() {
        return this->commandCode;
    }
    void MtxAppLayerMessage::setMtxRespParams(MessageDecoder* mtxRespParams) {
        this->mtxRespParams = mtxRespParams;
    }
    bool MtxAppLayerMessage::decode(uint8_t* buffer, uint32_t len) {
        if(len < 2) {
            return false;
        }
        memcpy(&this->commandCode, buffer, 2);

        if(this->mtxRespParams != nullptr) {
            this->mtxRespParams->decode(&buffer[2], len - 2);
        }
        return true;
    }
    uint32_t MtxAppLayerMessage::getLen() {
        uint32_t len = sizeof(this->commandCode);
        if(this->mtxRespParams != nullptr) {
            len += this->mtxRespParams->getLen();
        }
        return len;
    }

    void MtxFileRWPLParams::setBuffer(uint8_t* buffer) {
        this->buffer = buffer;
    }
    void MtxFileRWPLParams::setLen(uint32_t len) {
        this->len = len;
    }
    uint8_t* MtxFileRWPLParams::getBuffer() {
        return this->buffer;
    }
    uint32_t MtxFileRWPLParams::getBufferLen() {
        return this->len;
    }
    bool MtxFileRWPLParams::decode(uint8_t* buffer, uint32_t len) {
        this->buffer = buffer;
        this->len = len;
        return true;
    }
    uint32_t MtxFileRWPLParams::getLen() {
        return this->len;
    }

    void MtxPresLayerMessage::setPLParams(MessageDecoder* aLParams) {
        this->aLParams = aLParams;
    }
    void MtxPresLayerMessage::setLayerMessage(MessageDecoder* layerMessage) {
        this->layerMessage = layerMessage;
    }
    bool MtxPresLayerMessage::decode(uint8_t* buffer, uint32_t len) {
        this->layerMessage->decode(buffer, len);
        if(len < this->layerMessage->getLen()) {
            return false;
        }
        if(this->aLParams != nullptr) {
            this->aLParams->decode(&buffer[this->layerMessage->getLen()], len - this->layerMessage->getLen());
        }
        return true;
    }
    uint32_t MtxPresLayerMessage::getLen() {
        uint32_t len = 0;
        if(this->aLParams != nullptr) {
            len += this->aLParams->getLen();
        }
        if(this->layerMessage != nullptr) {
            len += this->layerMessage->getLen();
        }
        return len;
    }

}

}
}