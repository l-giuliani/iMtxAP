#include "mtxLayers.h"

#include <cstring>
#include "mtxDto.h"
#include "mtxProtocol.h"

namespace NProtocols {
namespace NLayers {

    NProtocols::NLayers::SerialDLLayer* MtxPresLayer::getLinkLayer() {
        return (&this->serialDLLayer);
    }
    NProtocols::NLayers::SerialDLLayer* MtxAppLayer::getLinkLayer() {
        return this->mtxPresLayer.getLinkLayer();
    }

    void MtxAppLayer::sendReadFileRequest(uint8_t* buffer, char* filename, uint32_t offset, uint32_t size) {
        NProtocols::NDto::NEncoders::MtxAppLayerMessage mtxAppMessage;
        mtxAppMessage.setCommandCode(NProtocols::NLibs::MTX_COMMANDS::COMMAND_READ_FILE);
        NProtocols::NDto::NEncoders::MtxFileRWParams mtxRWParams;
        mtxRWParams.setOffset(offset);
        mtxRWParams.setLen(size);
        mtxRWParams.setFilename(filename);
        mtxRWParams.setFilenameLen(strlen(filename));

        mtxAppMessage.setMtxReqParams(&mtxRWParams);
        
        this->mtxPresLayer.sendReadFileRequest(mtxAppMessage, buffer);
    }

    /**
    *   @return -1 error received, 0 decode error, 1 ok
    */
    int MtxAppLayer::recvReadFileResponse(uint8_t* buffer, uint8_t** data, uint32_t& len) {
        NProtocols::NDto::NDecoders::MtxAppLayerMessage mtxAppMessage;
        NProtocols::NDto::NDecoders::MtxFileRWPLParams mtxRWParams;
        NProtocols::NDto::NDecoders::MtxPresLayerMessage mtxPresLayerMessage;
        mtxPresLayerMessage.setPLParams(&mtxRWParams);
        mtxPresLayerMessage.setLayerMessage(&mtxAppMessage);

        int res = this->mtxPresLayer.recvReadFileResponse(buffer, mtxPresLayerMessage);
        if(res != 1) {
            return res;
        }

        if(NProtocols::NLibs::MTX_COMMANDS::COMMAND_READ_FILE != mtxAppMessage.getCommandCode()) {
            return -1;
        }

        *data = mtxRWParams.getBuffer();
        len = mtxRWParams.getBufferLen();

        return 1;
    }
    void MtxAppLayer::sendWriteFileRequest(uint8_t* buffer, char* filename, uint8_t* data, uint32_t offset, uint32_t size) {
        NProtocols::NDto::NEncoders::MtxAppLayerMessage mtxAppMessage;
        mtxAppMessage.setCommandCode(NProtocols::NLibs::MTX_COMMANDS::COMMAND_WRITE_FILE);
        NProtocols::NDto::NEncoders::MtxFileRWParams mtxRWParams;
        mtxRWParams.setOffset(offset);
        mtxRWParams.setLen(size);
        mtxRWParams.setFilename(filename);
        mtxRWParams.setFilenameLen(strlen(filename));

        mtxAppMessage.setMtxReqParams(&mtxRWParams);
        
        this->mtxPresLayer.sendWriteFileRequest(mtxAppMessage, buffer, data, size);
    }
    /**
    *   @return -1 error received, 0 decode error, 1 ok
    */
    int MtxAppLayer::recvWriteFileResponse(uint8_t* buffer) {
        NProtocols::NDto::NDecoders::MtxAppLayerMessage mtxAppMessage;
        NProtocols::NDto::NDecoders::MtxPresLayerMessage mtxPresLayerMessage;
        mtxPresLayerMessage.setLayerMessage(&mtxAppMessage);
        
        int res = this->mtxPresLayer.recvWriteFileResponse(buffer, mtxPresLayerMessage);
        if(res != 1) {
            return res;
        }

        if(NProtocols::NLibs::MTX_COMMANDS::COMMAND_WRITE_FILE != mtxAppMessage.getCommandCode()) {
            return -1;
        }
        return 1;
    }

    void MtxPresLayer::sendReadFileRequest(NProtocols::NDto::NEncoders::MtxAppLayerMessage& mtxAppMessage, uint8_t* buffer) {
        NProtocols::NDto::NEncoders::MtxPresLayerMessage mtxPresLayerMessage;
        NProtocols::NDto::NEncoders::MtxFileRWPLParams mtxFileRWPLParams;
        mtxPresLayerMessage.setPLParams(&mtxFileRWPLParams);
        mtxPresLayerMessage.setLayerMessage(&mtxAppMessage);

        serialDLLayer.send(&mtxPresLayerMessage, buffer);
    }

    /**
     * @return -1 reading error, 0, decode error, 1 ok
     */
    int MtxPresLayer::recvReadFileResponse(uint8_t* buffer, NProtocols::NDto::NDecoders::MtxPresLayerMessage& message) {
        uint8_t** t_buffer = &buffer;

        int len = serialDLLayer.readResponse(t_buffer, 1024);
        if (len < 0) {
            return len;
        }
        bool decodeRes = message.decode(*t_buffer, len);
        if(!decodeRes) {
            return 0;
        }
        return 1;
    }

    void MtxPresLayer::sendWriteFileRequest(NProtocols::NDto::NEncoders::MtxAppLayerMessage& mtxAppMessage, uint8_t* buffer, uint8_t* data, uint32_t size) {
        NProtocols::NDto::NEncoders::MtxPresLayerMessage mtxPresLayerMessage;
        NProtocols::NDto::NEncoders::MtxFileRWPLParams mtxFileRWPLParams;

        mtxFileRWPLParams.setBuffer(data);
        mtxFileRWPLParams.setLen(size);

        mtxPresLayerMessage.setPLParams(&mtxFileRWPLParams);
        mtxPresLayerMessage.setLayerMessage(&mtxAppMessage);

        serialDLLayer.send(&mtxPresLayerMessage, buffer);
    }

    /**
     * @return -1 reading error, 0, decode error, 1 ok
     */
    int MtxPresLayer::recvWriteFileResponse(uint8_t* buffer, NProtocols::NDto::NDecoders::MtxPresLayerMessage& message) {
        uint8_t** t_buffer = &buffer;

        int len = serialDLLayer.readResponse(t_buffer, 256);
        if (len < 0) {
            return len;
        }
        bool decodeRes = message.decode(*t_buffer, len);
        if(!decodeRes) {
            return 0;
        }
        return 1;
    }

}
}