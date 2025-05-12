#include "protocolsDto.h"

namespace NProtocols {
namespace NDto {

void SerialDLMessage::setStationCode(uint16_t stationCode) {
    this->stationCode = stationCode;
}

void SerialDLMessage::setChecksum(uint16_t checksum) {
    this->checksum = checksum;
}

void SerialDLMessage::setLayerMessage(MessageEncoder* layerMessage) {
    this->layerMessage = layerMessage;
}

void SerialDLMessage::encode(uint8_t* buffer) {

}

uint32_t SerialDLMessage::getLen() {
    uint32_t len;
	len = sizeof(this->stationCode) + sizeof(this->checksum);
	if(this->layerMessage != nullptr) {
		len += this->layerMessage->getLen();
	}
	return len;
}

}
}