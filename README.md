# iMtxAP

### What is iMtxAP

iMtxAp is a reduced initial version of a component of an embedded system.
iMtxAP runs on a ESP32-C3 Mini board and acts as an access point in order to translate HTTP requests into serial commands sent to other parts of the system.

### Supported Commands 
In this version, commands for reading from and writing to portions of files are supported. Two HTTP endpoints are provided in order to perform these operations. HTTP requests are translated into one or more serial requests using a custom protocol called mtx.

### Endpoints

| Request type | Endpoint | Query params                                                 | Body                                 | Response                        |
| ------------ | -------- | ------------------------------------------------------------ | ------------------------------------ | ------------------------------- |
| GET          | /file    | filename: the name of the file<br/>offset: offset<br/>size: quantity of bytes |                                      | The bytes of the file requested |
| POST         | /file    | filename: the name of the file<br/>offset: offset            | bytes of file that has to be written | code 201 if ok                  |