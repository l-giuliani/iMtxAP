#ifndef _PROTOCOLLIBS_H_
#define _PROTOCOLLIBS_H_

#include <cstdint>

namespace NProtocols {
namespace NLibs { 

    class Checksum {
    public:
	    virtual uint16_t calcChecksum(uint8_t* buffer, uint32_t len) = 0;
    };

    class SumChecksum : public Checksum {
    public:
        uint16_t calcChecksum(uint8_t* buffer, uint32_t len);
    };

}
}

#endif // _PROTOCOLLIBS_H