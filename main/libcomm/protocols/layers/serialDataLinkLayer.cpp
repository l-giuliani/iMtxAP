#include "serialDataLinkLayer.h"

#include <cstring>

namespace NProtocols {
namespace NLayers {

void SerialDLLayer::setStationId(uint16_t stationId) {
    this->stationId = stationId;
}

void SerialDLLayer::setTimeout(uint32_t timeout) {
    this->timeout = timeout;
}

void SerialDLLayer::setUart(NDrivers::Uart* uart) {
    this->uart = uart;
}

void SerialDLLayer::send(NProtocols::NDto::MessageEncoder* message, uint8_t* buffer) {
    uint32_t len;
    memcpy(buffer, &this->stationId, 2);
    len = 2;
    message->encode(&buffer[len]);
    len += message->getLen();
    uint16_t ck = this->checksum.calcChecksum(buffer, len);
    memcpy(&buffer[len], &ck, 2);
    len += 2;
    
    this->uart->write(buffer, len);
}

int SerialDLLayer::readResponse(uint8_t** buffer, uint32_t maxlen) {
    int len = this->uart->read(*buffer, maxlen, this->timeout, 100);
    if(len < 3) {
        return -1;
    } 
    uint16_t r_checksum;
    memcpy(&r_checksum, &(*buffer)[len - 2], 2);
    uint16_t c_checksum = this->checksum.calcChecksum(*buffer, len - 2); 
    if(r_checksum != c_checksum) { 
        return -1;
    }
    *buffer += 2;
    return (len - 4);
}

}
}