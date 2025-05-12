# iMtxAP

### What is iMtxAP

iMtxAp is a first reduced version of a portion of an embedded system.
iMtxAP runs on a ESP32 c3 mini board and acts as an access point in order to translate http requests in serial commands to other parts of the system.

### Commands supported
In this version, commands to read and write portions of files are supported. Two endpoints are provided in order to perform these operations. HTTP requests  are translated in one or multiple requests over serial port, serial requests are coded in a custom protocol called mtx.

### Endpoints

| Request type | Endpoint | Query params                                                 | Body                                 | Response                        |
| ------------ | -------- | ------------------------------------------------------------ | ------------------------------------ | ------------------------------- |
| GET          | /file    | filename: the name of the file<br/>offset: offset<br/>size: quantity of file bytes |                                      | The bytes of the file requested |
| POST         | /file    | filename: the name of the file<br/>offset: offset            | bytes of file that has to be written | code 201 if ok                  |