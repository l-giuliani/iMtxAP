#ifndef _MTXDTO_H_
#define _MTXDTO_H_

#include <cstdint>
#include "protocolsDto.h"

namespace NProtocols {
namespace NDto {

namespace NEncoders {

class MtxAppLayerMessage : public NProtocols::NDto::MessageEncoder {
private:
    uint16_t commandCode;
    NProtocols::NDto::MessageEncoder* mtxReqParams;
public:
    void setCommandCode(uint16_t commandCode);
    void setMtxReqParams(MessageEncoder* mtxReqParams);
	void encode(uint8_t* buffer);
	uint32_t getLen();
};

class MtxFileRWParams : public NProtocols::NDto::MessageEncoder {
private:
    uint16_t offset;
    uint8_t len;
    uint8_t filenameLen;
    char* filename;
public:
    void setOffset(uint16_t offset);
    void setLen(uint8_t len);
    void setFilenameLen(uint8_t filenameLen);
    void setFilename(char* filename);
    void encode(uint8_t* buffer);
	uint32_t getLen();
};

class MtxFileRWPLParams : public NProtocols::NDto::MessageEncoder {
private:
    uint8_t* buffer = nullptr;
    uint32_t len = 0;
public:
    void setBuffer(uint8_t* buffer);
    void setLen(uint32_t len);
    uint32_t getSize();
    void encode(uint8_t* buffer);
	uint32_t getLen();
};

class MtxPresLayerMessage : public NProtocols::NDto::MessageEncoder {
private:
    NProtocols::NDto::MessageEncoder* pLParams;
    NProtocols::NDto::MessageEncoder* layerMessage;
public:
    void setPLParams(MessageEncoder* pLParams);
    void setLayerMessage(MessageEncoder* layerMessage);
    void encode(uint8_t* buffer);
	uint32_t getLen();
};

}

namespace NDecoders {

    class MtxAppLayerMessage : public NProtocols::NDto::MessageDecoder {
    private:
    uint16_t commandCode;
        NProtocols::NDto::MessageDecoder* mtxRespParams = nullptr;
    public:
        void setCommandCode(uint16_t commandCode);
        uint16_t getCommandCode();
        void setMtxRespParams(MessageDecoder* mtxRespParams);
        bool decode(uint8_t* buffer, uint32_t len);
        uint32_t getLen();
    };

    class MtxFileRWPLParams : public NProtocols::NDto::MessageDecoder {
    private:
        uint8_t* buffer = nullptr;
        uint32_t len = 0;
    public:
        void setBuffer(uint8_t* buffer);
        void setLen(uint32_t len);
        uint8_t* getBuffer();
        uint32_t getBufferLen();
        bool decode(uint8_t* buffer, uint32_t len);
        uint32_t getLen();
    };

    class MtxPresLayerMessage : public NProtocols::NDto::MessageDecoder {
    private:
        NProtocols::NDto::MessageDecoder* aLParams = nullptr;
        NProtocols::NDto::MessageDecoder* layerMessage = nullptr;
    public:
        void setPLParams(MessageDecoder* aLParams);
        void setLayerMessage(MessageDecoder* layerMessage);
        bool decode(uint8_t* buffer, uint32_t len);
        uint32_t getLen();
    };

}

}
}

#endif // _MTXDTO_H