#include "protocolLibs.h"

namespace NProtocols {
namespace NLibs {

    uint16_t SumChecksum::calcChecksum(uint8_t* buffer, uint32_t len) {
        uint16_t sum1 = 0;
        uint16_t sum2 = 0;
        for (uint32_t i = 0; i < len; ++i) {
            sum1 = (sum1 + buffer[i]) % 255;
            sum2 = (sum2 + sum1) % 255;
        }
        return (sum2 << 8) | sum1;
    }

}
}