#include "dataServices.h"

#include "mtxProtocol.h"

extern NProtocols::MtxProtocol mtxProtocol;

namespace NDataServices {

    /**
     * @return -1 error, 1 ok
     */
    int Services::readFile(httpd_req_t *b_req, char* filename, uint32_t offset, uint32_t size, ChunkEndpoint chunkEndpoint) {
        uint8_t buffer[1024];
        uint8_t r_buffer[1024];
        uint8_t* f_ptr;
        uint32_t f_len;
        uint32_t chunkNum = size / MAX_FILE_READ_LEN;
        if((size % MAX_FILE_READ_LEN) != 0) {
            chunkNum++;
        } 

        uint32_t currOffset = offset;
        uint32_t currSize;
        if(chunkNum > 1) {
            currSize = MAX_FILE_READ_LEN;
        } else {
            currSize = size;
        }
        while (chunkNum > 0) {
            mtxProtocol.sendReadFileRequest(buffer, filename, currOffset, currSize);
            int res = mtxProtocol.recvReadFileResponse(r_buffer, &f_ptr, f_len);
            if(res != 1) {
                return -1;
            }

            chunkEndpoint(b_req, f_ptr, f_len);

            if(chunkNum > 1 && f_len < currSize) {
                break;
            }

            chunkNum--;
            currOffset += f_len;
            if(chunkNum > 1) {
                currSize = MAX_FILE_READ_LEN;
            } else {
                currSize = size % MAX_FILE_READ_LEN;
            }
        }
        return 1;
    }

    /**
     * @return -1 error, 1 ok
     */
    int Services::writeFile(char* filename, uint8_t* data, uint32_t offset, uint32_t size) {
        uint8_t buffer[1024];
        uint8_t r_buffer[1024];
        uint32_t chunkNum = size / MAX_FILE_WRITE_LEN;
        if((size % MAX_FILE_WRITE_LEN) != 0) {
            chunkNum++;
        } 

        uint32_t currOffset = offset;
        uint32_t currSize;
        if(chunkNum > 1) {
            currSize = MAX_FILE_WRITE_LEN;
        } else {
            currSize = size;
        }

        while (chunkNum > 0) {
            mtxProtocol.sendWriteFileRequest(buffer, filename, &data[currOffset - offset], currOffset, currSize);
            int res = mtxProtocol.recvWriteFileResponse(r_buffer);
            if(res != 1) {
                return -1;
            }

            chunkNum--;
            currOffset += currSize;
            if(chunkNum > 1) {
                currSize = MAX_FILE_WRITE_LEN;
            } else {
                currSize = size % MAX_FILE_WRITE_LEN;
            }
        }
        return 1;
    }

}