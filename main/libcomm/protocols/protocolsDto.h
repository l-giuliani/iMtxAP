#ifndef _PROTOCOLSDTO_H_
#define _PROTOCOLSDTO_H_

#include <cstdint>

namespace NProtocols {
namespace NDto {

class MessageDecoder {
public:
    virtual bool decode(uint8_t* buffer, uint32_t len) = 0;
    virtual uint32_t getLen() = 0;
};

class MessageEncoder {
public:
	virtual void encode(uint8_t* buffer) = 0;
	virtual uint32_t getLen() = 0;
};

class SerialDLMessage : public MessageEncoder {
private:
    uint16_t stationCode;
    MessageEncoder* layerMessage;
    uint16_t checksum;
public:
    void setStationCode(uint16_t stationCode);
    void setChecksum(uint16_t checksum);
    void setLayerMessage(MessageEncoder* layerMessage);
    void encode(uint8_t* buffer);
    uint32_t getLen();
};

}
}

#endif // _PROTOCOLSDTO_H