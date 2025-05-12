#include "uart.h"

#include "appconf.h"
#include "freertos/FreeRTOS.h"

namespace NDrivers {

    Uart::Uart() {
        this->baudrate = (uint32_t)UART_BAUDRATE;
        this->dataBits = UART_DATA_BITS;
        this->parity = UART_PARITY;
        this->stopBits = UART_STOP_BITS;
        this->flowControl = UART_FLOW_CONTROL;

        this->txpin = UART_TX_PIN;
        this->rxpin = UART_RX_PIN;
    }

    void Uart::init(uart_port_t uartNum) {
        const int uart_buffer_size = (1024 * 2);
        QueueHandle_t uart_queue;
       
        this->uartNum = uartNum;

        ESP_ERROR_CHECK(uart_driver_install(this->uartNum, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
    
        uart_config_t uart_config;
        uart_config.baud_rate = this->baudrate;
        uart_config.data_bits = this->dataBits;
        uart_config.parity = this->parity;
        uart_config.stop_bits = this->stopBits;
        uart_config.flow_ctrl = this->flowControl;
        
        ESP_ERROR_CHECK(uart_param_config(this->uartNum, &uart_config));
        ESP_ERROR_CHECK(uart_set_pin(this->uartNum, this->txpin, this->rxpin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));    
    }

    int Uart::write(uint8_t* buffer, uint32_t len) {
        return uart_write_bytes(this->uartNum, (const char*)buffer, len);
    }

    int Uart::read(uint8_t* buffer, uint32_t maxlen, uint32_t startTimeout, uint32_t endTimeout) {
        int available = 0;
        int bytesReaded = 0;
        int len;

        for(int i = 0; i < (startTimeout/10); i++) {
            uart_get_buffered_data_len(this->uartNum, (size_t*)&available);
            if (available > 0) {
                break;
            }
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        if (available == 0) {
            return 0;
        }

        len = 0;
        do {
            bytesReaded = uart_read_bytes(this->uartNum, buffer + len, maxlen - len, pdMS_TO_TICKS(endTimeout));
            if (bytesReaded > 0) {
                len += bytesReaded;
            }            
        } while (bytesReaded > 0 && len < maxlen);

        return len;
    }

}