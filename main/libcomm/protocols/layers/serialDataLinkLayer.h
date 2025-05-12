#ifndef _SERIALDATALINKLAYER_H_
#define _SERIALDATALINKLAYER_H_

#include <cstdint>
#include "uart.h"
#include "protocolLibs.h"
#include "protocolsDto.h"

namespace NProtocols {
namespace NLayers {

class SerialDLLayer {
private:
    uint16_t stationId;
    NDrivers::Uart* uart;
    uint32_t timeout;
    NProtocols::NLibs::SumChecksum checksum;
public:
    void setStationId(uint16_t stationId);
    void setTimeout(uint32_t timeout); 
    void setUart(NDrivers::Uart* uart);
    void send(NProtocols::NDto::MessageEncoder* message, uint8_t* buffer);
    int readResponse(uint8_t** buffer, uint32_t maxlen);
};

}
}

#endif // _SERIALDATALINKLAYER_H