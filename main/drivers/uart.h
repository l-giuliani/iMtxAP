#ifndef _UART_H_
#define _UART_H_

#include <cstdint>
#include "driver/uart.h"

namespace NDrivers {

    class Uart {
    private:
        uint32_t baudrate;
        uart_port_t uartNum;
        uart_word_length_t dataBits;
        uart_parity_t parity;
        uart_stop_bits_t stopBits;
        uart_hw_flowcontrol_t flowControl;

        uint8_t txpin;
        uint8_t rxpin;
    public:
        Uart();
        void init(uart_port_t uartNum);
        int write(uint8_t* buffer, uint32_t len);
        int read(uint8_t* buffer, uint32_t maxlen, uint32_t startTimeout, uint32_t endTimeout);
    };

}

#endif // _UART_H